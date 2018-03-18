/**************************************************
  >File Name: proxy_log_debug.c
  >Author:silence
  >Create Time: 2018年02月01日 星期四 13时55分22秒
**************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <syslog.h>
#include <sys/stat.h> 

#include "PLog.h"

#define PROXY_LOG_BUF_SIZE  (4096) 

typedef enum {
	 OK = 0,         //成功
	 ERROR = -1,     //失败
	 ENDOFFILE = -2  //到文件结束
}funResult;


struct proxy_log_s {    
    int     level;
    int     type;
    char    name[32];
};

static int get_real_line(FILE *fp, char *line);

static void init_log(int level, const char *name, const char *filename);

static int config_parse_log(FILE *fp, int *log_level, int *log_model, char *log_file, size_t len);

/*
 * @param level 日志级别
 *                  PROXY_LOG_ERR
 *                  PROXY_LOG_WARN
 *                  PROXY_LOG_INFO
 *                  PROXY_LOG_DEBUG
 * @param type 日志输出形式
 *                  PROXY_LOG_TYPE_OUTPUT
 *                  PROXY_LOG_TYPE_FILE 
 * */
proxy_log_t *PLog_init(int level, int type, const char *name, const char *file)
{
#if 0
    if (type & PROXY_LOG_TYPE_OUTPUT) { 
        printf("---------- PROXY_LOG_TYPE_OUTPUT ----------\n"); 
    }
    if (type & PROXY_LOG_TYPE_FILE) {
        printf("----------- PROXY_LOG_TYPE_FILE ------------\n"); 
    }
#endif 

    proxy_log_t *plog = (proxy_log_t *)malloc(sizeof(proxy_log_t));
    if (plog == NULL) {
		printf("proxy_log_t malloc error\n");
		return NULL;   
	}
    memset(plog, 0, sizeof(proxy_log_t));

    plog -> type  = type;
    plog -> level = level;
    if (name != NULL)   strcpy(plog -> name, name);

    if ((type & PROXY_LOG_TYPE_FILE) && (file != NULL)) {
        // 系统日志处理
        init_log(level, name, file);
    }


    return plog;
}


void _PLog(int level, const proxy_log_t *log_info, const char *fmt, ...)  
{ 
    //if (log_info == NULL) return ;

    int     index;
    va_list ap;  
    char    buf[PROXY_LOG_BUF_SIZE];

	memset(buf, '\0', PROXY_LOG_BUF_SIZE);
    va_start(ap, fmt);  
    vsnprintf(buf, PROXY_LOG_BUF_SIZE, fmt, ap);  

	if (log_info == NULL) {
		if (level & PROXY_LOG_ERR) {
			printf("%s", buf);  
		}

	} else {
		if (log_info -> type & PROXY_LOG_TYPE_OUTPUT) { 
			if (level & log_info -> level) {
				printf("%s", buf);  
			}
		}  

		if (log_info -> type & PROXY_LOG_TYPE_FILE) {
			if (level & log_info -> level) {
				if (level & PROXY_LOG_DEBUG)  
					syslog(LOG_DEBUG, "%s", buf);
				else if (level & PROXY_LOG_INFO) 
					syslog(LOG_INFO, "%s", buf);  
				else if (level & PROXY_LOG_WARN)
					syslog(LOG_WARNING, "%s", buf);  
				else if (level & PROXY_LOG_ERR)
					syslog(LOG_ERR, "%s", buf);  
			}
		}
	}

	va_end(ap);  
	return ;
}


void PLog_close(proxy_log_t *log_info)
{
	if (log_info != NULL)
		free(log_info);

	return ;
}

static void init_log(int level, const char *name, const char *filename)
{
	int logfd; 


	//if      (level & PROXY_LOG_DEBUG)   setlogmask(LOG_UPTO(LOG_DEBUG));
	//else if (level & PROXY_LOG_INFO)    setlogmask(LOG_UPTO(LOG_INFO));
	//else if (level & PROXY_LOG_WARN)    setlogmask(LOG_UPTO(LOG_WARNING));
	//else if (level & PROXY_LOG_ERR)     setlogmask(LOG_UPTO(LOG_ERR));


	logfd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);

	//将标准错误输出重定向到日志文件
	close(2);
	dup2(logfd, 2);
	close(logfd);

	//openlog会将name加载所有的日志前面
	//openlog(name, LOG_PERROR|LOG_NDELAY|LOG_NOWAIT|LOG_CONS|LOG_PID, LOG_USER);
	openlog(name, LOG_PERROR | LOG_CONS | LOG_NDELAY | LOG_PID, LOG_USER);

	return ;
}

/////////////////////////////////////////////////////////////////////////////////

#ifndef LINE_SIZE
#define LINE_SIZE	1024
#endif

int Read_Log_File(char *cfgfile, int *level, int *model, char *file, size_t len)
{
	if (cfgfile == NULL)	return ERROR;
	if (level == NULL || model == NULL)		return ERROR;

	FILE *fp = fopen(cfgfile, "r");
	if(fp == NULL) {
		printf("fopen %s error\n", cfgfile);
		return ERROR;
	}

	char line[LINE_SIZE];
	while(1)
	{
		//读入到文件结束	
		if(get_real_line(fp, line) == ENDOFFILE)
			break;

		if(strcmp(line, "Log") == 0) {			//基本配置 
			if(config_parse_log(fp, level, model, file, len) == ERROR) {
				goto OUT_ERROR;
			}

			break;	// 遇到第一个为准
		}
	}

	fclose(fp);

	return OK;

OUT_ERROR:
	return ERROR;
}

static int config_parse_log(FILE *fp, int *log_level, int *log_model, char *log_file, size_t len)
{
	char line[LINE_SIZE];
	char key[LINE_SIZE];
	char value[LINE_SIZE];

	if(get_real_line(fp, line) == ENDOFFILE) {
		printf("log cfgfile: no content\n");
		return ERROR;
	}

	if(strcmp(line, "{") != 0) {
		printf("log cfgfile: not begin with '{'\n");
		return ERROR;
	}

	while(1)
	{
		//读入到文件结束	
		if(get_real_line(fp, line) == ENDOFFILE) {
			printf("log cfgfile: not end with '}'\n");
			return ERROR;
		}

		int num = sscanf(line, "%[^=]=%s", key, value);
		if(strcmp(line, "}") == 0) {

			return OK;

		} else {
			if(num != 2) {
				printf("log cfgfile: format error\n");
				return ERROR;
			}

			if(strcmp(key, "log_level_err") == 0) {			// 日志级别为 ERR
				if (!strcasecmp(value, "ON")) {				// 开启ERR日志级别
					if (*log_level == 0)	*log_level = PROXY_LOG_ERR;
					else	*log_level = *log_level | PROXY_LOG_ERR;
				}
			}
			else if(strcmp(key, "log_level_warn") == 0) {
				if (!strcasecmp(value, "ON")) {
					if (*log_level == 0)	*log_level = PROXY_LOG_WARN;
					else	*log_level = *log_level | PROXY_LOG_WARN;
				}
			}
			else if(strcmp(key, "log_level_info") == 0) {
				if (!strcasecmp(value, "ON")) {
					if (*log_level == 0)	*log_level = PROXY_LOG_INFO;
					else	*log_level = *log_level | PROXY_LOG_INFO;
				}
			}
			else if(strcmp(key, "log_level_debug") == 0) {
				if (!strcasecmp(value, "ON")) {
					if (*log_level == 0)	*log_level = PROXY_LOG_DEBUG;
					else	*log_level = *log_level | PROXY_LOG_DEBUG;
				}
			}
			else if(strcmp(key, "log_model_output") == 0) {
				if (!strcasecmp(value, "ON")) {
					if (*log_model == 0)	*log_model = PROXY_LOG_TYPE_OUTPUT;
					else	*log_model = *log_model | PROXY_LOG_TYPE_OUTPUT;
				}
			}
			else if(strcmp(key, "log_model_file") == 0) {
				if (!strcasecmp(value, "ON")) {
					if (*log_model == 0)	*log_model = PROXY_LOG_TYPE_FILE;
					else	*log_model = *log_model | PROXY_LOG_TYPE_FILE;
				}
			}
			else if(strcmp(key, "log_file") == 0) {
				if (log_file != NULL && (strlen(value) < len))	{
					strcpy(log_file, value);
				} else {
					*log_model = PROXY_LOG_TYPE_OUTPUT; 
				}
			}
			else {
				printf("log cfgfile: can't recognise\n");
				continue;
			}
		}
	}

	return OK;
}

/*
 **	得到配置文件中真正的有意义的一行，忽略空行和注释行
 */
static int get_real_line(FILE *fp, char *line)
{
	char buf[LINE_SIZE];
	while(1)
	{
		if(fgets(buf, LINE_SIZE, fp) == NULL)		
			return ENDOFFILE;
		char *pstr = buf;
		while(*pstr!='\0' && (*pstr==' ' || *pstr=='\t' || *pstr=='\n'))
			pstr++;

		if(*pstr!='#' && *pstr!='\0')
			break;
	}

	//去掉此行中的空白字符和注释
	int i = 0, j = 0;
	while(1)
	{
		if(buf[i] != '\0' && (buf[i]==' ' || buf[i]=='\t' || buf[i]=='\n'))
		{
			i++;
			continue;
		}

		if(buf[i]=='#' || buf[i]=='\0')
			break;

		line[j++] = buf[i++];
	}
	line[j] = '\0';

	// printf("line: %s\n", line);
	return OK;
}
