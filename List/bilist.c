#include"bilist.h"
#include	<pthread.h>


void list_init(list *l)
{
    l->count=0;
    l->front=NULL;
    l->rear=NULL;
}


void Queue_init(list *Q)
{
    pthread_mutex_init(&Q->qlock,NULL);
    pthread_cond_init(&Q->qready,NULL);
    Q->front=NULL;
    Q->rear=NULL;
}

//入队
void list_append(list *l,list_node *node)
{
    node->prev=l->rear;
    node->next=NULL;
    if(l->front==NULL)
    {
        l->front=node;
    }
    else
    {
        l->rear->next=node;
    }
    l->rear=node;
    l->count++;
}

//出队
list_node *list_pop(list *l)
{
    if(l->front==NULL)
        return NULL;
    list_node  *r=l->front;
    l->front=l->front->next;
    if (l->front == NULL)
    {
        l->rear=NULL;
    }
    else
        l->front->prev=NULL;
    l->count--;
    return r;
}

void  list_push(list *l,list_node *node)
{
    if(l->front==NULL)
    {
       l->front=node;
       l->rear=node;
    }
    else
    {
        node->next=l->front;
        l->front->prev=node;
        l->front=node;
        node->prev=NULL;
    }
    l->count++;
}


void list_del(list *l,list_node *node)
{
    if(node->prev==NULL)
    {
        l->front=node->next;
    }
    else
    {
        node->prev->next=node->next;
    }
    if(node->next==NULL)
    {
        l->rear=node->prev;
    }
    else
    {
        node->next->prev=node->prev;
    }
    l->count--;
}


list_node  *DeQueueLock(list *Q)
{//取结果
    pthread_mutex_lock(&Q->qlock);
    while(Q->front==NULL)
        pthread_cond_wait(&Q->qready,&Q->qlock);
    list_node *p=list_pop(Q);
    pthread_mutex_unlock(&Q->qlock);
    return p;
}

void EnQueueLock(list *Q,list_node *node)
{//入队，存结果
    pthread_mutex_lock(&Q->qlock);
    list_append(Q,node);
    pthread_cond_signal(&Q->qready);
    pthread_mutex_unlock(&Q->qlock);
}



