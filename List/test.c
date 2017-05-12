/*******************************************************************
 ** Copyright(c) 2016,哈尔滨工程大学信息安全研究中心
 ** All rights reserved
 ** 
 ** 文件名: a.c
 ** 创建人: zhengli
 ** 描  述: 
 ** 注  意: 
 ** 
 ** 当前版本：v1.0
 ** 作    者：zhengli
 ** 邮    箱: 
 ** 创建时间: 2016年12月03日 星期六 18时23分28秒
 ** 完成日期: 
 ******************************************************************/ 

#include	"bilist.h"
#include	<pthread.h>

#define BLACK_LIST 0
#define WHITE_LIST 1

typedef struct 
{
	list_node node;
	char ip[128];
	char url[128];
	int type;
}log_t;


void *thr_add_log(void* log);

list Queue;


#if 1
int main()
{
	int err;
	pthread_t pid_log;

	//日志任务队列初始化
	Queue_init(&Queue);

	//创建写日志线程
	err = pthread_create(&pid_log, NULL, thr_add_log, NULL);
	if(err != 0)
	{
		printf("create thr error\n");
		strerror(err);
		return -1;	
	}


	//添加任务
	char *ip01  = "192.168.121.1";
	char *url01 = "www.baidu.com";
	int  type01 = WHITE_LIST;
	log_t *log;
	log = (log_t *)malloc(sizeof(log_t));

	strcpy(log->ip, ip01);
	strcpy(log->url, url01);
	log->type = type01;
	EnQueueLock(&Queue, &log->node);

	char *ip02  = "192.168.121.2";
	char *url02 = "www.sina.com.cn";
	int  type02 = BLACK_LIST;
	log = (log_t *)malloc(sizeof(log_t));

	strcpy(log->ip, ip02);
	strcpy(log->url, url02);
	log->type = type02;

	EnQueueLock(&Queue, &log->node);


	sleep(2);

	char *ip04  = "192.168.121.4";
	char *url04 = "www.aaaa.com";
	int  type04 = WHITE_LIST;
	log = (log_t *)malloc(sizeof(log_t));

	strcpy(log->ip, ip04);
	strcpy(log->url, url04);
	log->type = type04;

	EnQueueLock(&Queue, &log->node);

	sleep(50);
	return 0;
}


void *thr_add_log(void* log)
{
	list_node *node;
	log_t *tack_log;
	while(1)
	{
		node = DeQueueLock(&Queue);	
		tack_log = (log_t*)node;
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
		printf("ip: %s, url: %s, type: %d\n", 
				tack_log->ip, 
				tack_log->url,
				tack_log->type);
		usleep(1000);
	}
	return NULL;
}
#endif
