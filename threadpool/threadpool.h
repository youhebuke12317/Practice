#ifndef	__PTHREADPOOL_H_
#define	__PTHREADPOOL_H_

#include	<stdio.h>
#include	<pthread.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<string.h>
#include	<signal.h>
#include	<errno.h>

#define		DEFAULT_THREAD_VARY	10
#define		true	1
#define		false	0

typedef struct threadpool_t threadpool_t;

typedef struct{
	void *(*function)(void *);  //函数指针
	void *arg;
}threadpool_task_t;

struct threadpool_t{
	pthread_mutex_t		lock;
	pthread_mutex_t		thread_counter;
	pthread_cond_t		queue_not_full;
	pthread_cond_t		queue_not_empty;

	pthread_t		*threads;
	pthread_t		adjust_tid;
	int		min_thr_num;
	int		max_thr_num;
	int 	live_thr_num;
	int 	busy_thr_num;
	int 	wait_exit_thr_num;

	threadpool_task_t	*task_queue;
	int 	queue_front;
	int		queue_rear;
	int 	queue_size;
	int		queue_max_size;

	int		shutdown;
};



/**
 * @function threadpool_create
 */
extern threadpool_t 
*threadpool_create(int min_thr_num, int max_thr_num, int queue_max_size);

/**
 * @function 
 */
extern int 
threadpool_add(threadpool_t *pool, void *(*function)(void *arg), void *arg);

/**
 * @function 
 */
extern int 
threadpool_destroy(threadpool_t *pool);


#endif
