#ifndef BILIST_H
#define BILIST_H

#include<stdio.h>

#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include<netinet/in.h>
#include<dlfcn.h>
#include<stdint.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//链表基本操作
typedef struct list_node
{
    struct list_node *prev;
    struct list_node *next;
}list_node;

typedef struct list
{
    unsigned int count;
    list_node *front;
    list_node *rear;
    pthread_mutex_t qlock;
    pthread_cond_t qready;
}list;


extern void list_init(list *l);
extern void Queue_init(list *Q); //带条件变量和互斥变量的初始化
//入队操作
extern void list_append(list *l,list_node *node);
extern void list_push(list *l,list_node *node);
extern void EnQueueLock(list *Q,list_node *node);
//出队操作
extern list_node  *list_pop(list *l);
extern list_node *DeQueueLock(list *Q);

extern void list_del(list *l,list_node *node);
#endif /*BILIST.H*/
