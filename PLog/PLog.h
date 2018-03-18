#ifndef __PROXY_LOG_DEBUG__
#define __PROXY_LOG_DEBUG__

typedef struct proxy_log_s          proxy_log_t; 

#if 1
//日志级别，由低到高，1-4
#define PROXY_LOG_ERR               1
#define PROXY_LOG_WARN              2
#define PROXY_LOG_INFO              4
#define PROXY_LOG_DEBUG             8
#endif

#if 0
typedef enum {
	PROXY_LOG_ERR = 1,
	PROXY_LOG_WARN,
	PROXY_LOG_INFO,
	PROXY_LOG_DEBUG
} Proxy_log_level;
#endif

#define    PROXY_LOG_TYPE_OUTPUT    1    // 日志输出在屏幕
#define    PROXY_LOG_TYPE_FILE      2    // 日志输出在文件


#define PLog_Info(level, log_info, fmt, ...)        																\
    _PLog(level, log_info, "[%s | %s() %d] "fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__)

#define PLog(level, log_info, fmt, ...)																				\
	if (level & PROXY_LOG_ERR) { PLog_Info(level, log_info, "[PROXY_LOG_ERR]"fmt, ##__VA_ARGS__); }					\
	else if (level & PROXY_LOG_WARN) { PLog_Info(level, log_info, "[PROXY_LOG_ERR]"fmt, ##__VA_ARGS__); }			\
	else if (level & PROXY_LOG_INFO) { PLog_Info(level, log_info, "[PROXY_LOG_INFO]"fmt, ##__VA_ARGS__); }			\
	else if (level & PROXY_LOG_DEBUG) { PLog_Info(level, log_info, "[PROXY_LOG_DEBUG]"fmt, ##__VA_ARGS__); }		\
	else { PLog_Info(level, log_info, "[NONE]"fmt, ##__VA_ARGS__); }

int Read_Log_File(char *cfgfile, int *level, int *model, char *file, size_t len);

proxy_log_t *PLog_init(int level, int type, const char *name, const char *file);

void _PLog(int level, const proxy_log_t *log_info, const char *fmt, ...);

void PLog_close(proxy_log_t *log_info);

#endif
