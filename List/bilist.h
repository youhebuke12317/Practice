#ifndef BILIST_H
#define BILIST_H

#include <pthread.h>

//链表基本操作
typedef struct list_node {
    struct list_node *prev;
    struct list_node *next;
}list_node;

typedef struct list {
    unsigned int	count;
    list_node		*front;
    list_node		*rear;
    pthread_cond_t	qready;
    pthread_mutex_t qlock;
}list;


extern void List_Init(list *l);
extern void Queue_Init(list *Q); 
//
//入队操作
extern void List_Append(list *l,list_node *node);
extern void List_Push(list *l,list_node *node);
extern void EnQueueLock(list *Q,list_node *node);

//出队操作
extern list_node  *List_Pop(list *l);
extern list_node  *DeQueueLock(list *Q);

extern void List_Del(list *l,list_node *node);


#endif /*BILIST.H*/
