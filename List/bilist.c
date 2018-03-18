#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <dlfcn.h>
#include <stdint.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "BiList.h"


/*
 * 链表初始化
 * */
void List_Init(list *l)
{
	if (!l)	return ;

    l -> count = 0;
    l -> front = NULL;
    l -> rear  = NULL;
}


/*
 * 链表初始化: 带条件变量和互斥变量的初始化
 * */
void Queue_Init(list *Q)
{
    pthread_mutex_init(&Q -> qlock,  NULL);
    pthread_cond_init (&Q -> qready, NULL);

	Q -> count = 0;
    Q -> front = NULL;
    Q -> rear  = NULL;
}

/*
 * 队列操作：入队
 * 从链表队列 尾 加入节点
 * */
void List_Append(list *l, list_node *node)
{
    node -> prev = l -> rear;
    node -> next = NULL;

    if(l -> front == NULL) {
        l -> front = node;
    } else {
        l -> rear -> next = node;
    }

    l -> rear = node;
    l -> count++;
}

/*
 * 队列操作：出队
 * 从链表队列 头 删除节点
 * */
list_node *List_Pop(list *l)
{
	list_node *ptr;

    if(l -> front == NULL)
        return NULL;

    ptr		  	    = l -> front;
    l -> front      = l -> front->next;

    if (l -> front == NULL) {
        l -> rear = NULL;
    } else {
        l -> front -> prev = NULL;
	}

    l -> count--;

    return ptr;
}




void  List_Push(list *l, list_node *node)
{
    if(l -> front == NULL) {
       l -> front = node;
       l -> rear  = node;
    } else {
        node -> next	   = l -> front;
        l -> front -> prev = node;
        l -> front         = node;
        node -> prev       = NULL;
    }

    l -> count++;
}


void List_Del(list *l, list_node *node)
{
    if(node -> prev == NULL) {
        l -> front = node -> next;
    } else {
        node -> prev -> next = node -> next;
    }

    if(node -> next == NULL) {
        l -> rear = node -> prev;
    } else {
        node -> next -> prev = node -> prev;
    }

    l->count--;
}



//取结果
list_node  *DeQueueLock(list *Q)
{
    pthread_mutex_lock(&(Q -> qlock));

    while(Q -> front == NULL)
        pthread_cond_wait(&(Q -> qready), &(Q -> qlock));

    list_node *p = List_Pop(Q);

    pthread_mutex_unlock(&(Q -> qlock));

    return p;
}

//入队，存结果
void EnQueueLock(list *Q, list_node *node)
{
    pthread_mutex_lock(&(Q -> qlock));

    List_Append(Q, node);

    pthread_cond_signal(&(Q-> qready));

    pthread_mutex_unlock(&(Q-> qlock));
}



