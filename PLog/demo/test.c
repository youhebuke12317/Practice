/**************************************************
  >File Name: test.c
  >Author:silence
  >Create Time: 2018年02月01日 星期四 15时46分23秒
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <proxyd/PLog.h>
#include "../PLog.h"

int  p_level;
int  p_model;
char p_file[128];

int main(int argc, char **argv)
{
    int i = 100;

//	p_model = PROXY_LOG_TYPE_FILE | PROXY_LOG_TYPE_OUTPUT;
//	p_level = PROXY_LOG_WARN | PROXY_LOG_DEBUG;
	
	//int Read_Log_File(char *cfgfile, int *level, int *model, char *file, size_t len);
	Read_Log_File("../log.conf", &p_level, &p_model, p_file, 128);

    proxy_log_t *plog;
    plog = PLog_init(p_level, p_model, argv[0], p_file);
    if (plog == NULL) return -1;

	while (1) {
		_PLog(PROXY_LOG_ERR,    plog, "this is log level: PROXY_LOG_ERR,    %d\n", i);
		_PLog(PROXY_LOG_WARN,   plog, "this is log level: PROXY_LOG_WARN,   %d\n", i);
		_PLog(PROXY_LOG_INFO,   plog, "this is log level: PROROXY_LOG_INFO, %d\n", i);
		_PLog(PROXY_LOG_DEBUG,  plog, "this is log level: PROXY_LOG_DEBUG,  %d\n", i);

		PLog(PROXY_LOG_ERR,    plog, "this is log level: PROXY_LOG_ERR,    %d\n", i);
		PLog(PROXY_LOG_WARN,   plog, "this is log level: PROXY_LOG_WARN,   %d\n", i);
		PLog(PROXY_LOG_INFO,   plog, "this is log level: PROROXY_LOG_INFO, %d\n", i);
		PLog(PROXY_LOG_DEBUG,  plog, "this is log level: PROXY_LOG_DEBUG,  %d\n", i);

		PLog_Info(PROXY_LOG_ERR,    plog, "this is log level: PROXY_LOG_ERR,    %d\n", i);
		PLog_Info(PROXY_LOG_WARN,   plog, "this is log level: PROXY_LOG_WARN,   %d\n", i);
		PLog_Info(PROXY_LOG_INFO,   plog, "this is log level: PROROXY_LOG_INFO, %d\n", i);
		PLog_Info(PROXY_LOG_DEBUG,  plog, "this is log level: PROXY_LOG_DEBUG,  %d\n", i);

		printf("\n\n");
		usleep(1000);
	}

	return 0;
}
