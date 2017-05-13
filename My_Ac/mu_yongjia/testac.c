/*******************************************************************
 ** Copyright(c) 2016,哈尔滨工程大学信息安全研究中心
 ** All rights reserved
 ** 
 ** 文件名: testac.c
 ** 创建人: zhengli
 ** 描  述: ac自动机的实现
 ** 注  意: 穆永佳的自动机，拿来参考学习
 ** 
 ** 当前版本：v1.0
 ** 作    者：zhengli
 ** 邮    箱: 2809411418@qq.com
 ** 创建时间: 2016年12月09日 星期五 08时02分18秒
 ** 完成日期: 
 ******************************************************************/ 


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TREEDATAMAX 256
#define MAXDATA 5
typedef struct tree_t
{
	struct tree_t* fail;    /***失败指针****/
	struct tree_t* next[TREEDATAMAX]; 
	int cnt;  
	unsigned char* s;
} tree;

void tree_init(tree* tr)
{
	memset(tr->next,0,sizeof(tr->next));
	tr->fail=NULL;
	tr->cnt=0;
	/**memset(tr->data,0,sizeof(tr->data));  ***/
}

tree* make_tree()
{
	tree* p = (tree*) malloc( sizeof(tree) );
	tree_init(p);
	return p;
}
/*************************************************队列************************************************/

typedef tree* QElemType;
typedef int Status;
#define OVERFLOW -1
#define OK 0
#define TRUE 1
#define FALSE 0
#define ERROR -1024
typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}*QueuePtr;

typedef struct Queue
{
	QueuePtr front,rear; /***对头队尾指针***/

} LinkQueue;

Status InitQueue(LinkQueue **Q)
{
	/**构造一个空队列***/

	if(!((*Q)->front = (*Q)->rear =(struct QNode *)malloc(sizeof(struct QNode))))
		exit(OVERFLOW);
	(*Q)->front->next = NULL;
	return OK;
}

Status DestroyQueue(LinkQueue *Q)
{
	/**销毁队列Q  ***/

	while(Q->front)
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	return OK;
}

Status ClearQueue(LinkQueue *Q)
{
	/***将Q清为空***/

	QueuePtr p,q;
	Q->rear = Q->front;
	p = Q->front->next;
	Q->front->next = NULL;
	while(p)
	{
		q = p;
		p=p->next;
		free(q);
	}
	return OK;
}

Status QueueEmpty(LinkQueue *Q)
{
	/***若Q为空队列，则返回TRUE，否则返回FALSE **/

	if(Q->front == Q->rear)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int QueueLength(LinkQueue *Q)
{
	/**求队列的长度**/

	int i=0;
	QueuePtr p;
	p = Q->front;
	while(Q->rear !=p)
	{
		i++;
		p=p->next;
	}
	return i;
}

Status GetHead(LinkQueue *Q,QElemType *e)
{
	/**若队列不空，用e返回Q的队头元素，并返回OK ，否则返回ERROR; **/

	QueuePtr p;
	if(Q->front == Q->rear)
		return ERROR;
	p=Q->front->next;
	*e = p->data;
	return OK;
}

Status EnQueue(LinkQueue *Q,QElemType e)
{
	/**插入元素e为Q的新的队尾元素**/

	QueuePtr p;
	if(!(p = (QueuePtr)malloc(sizeof(struct QNode))))
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
	return OK;
}

Status DeQueue(LinkQueue *Q,QElemType *e)
{
	/**若队列不空，删除Q的队头元素，用e返回其值，并返回OK，否则返回ERROR  **/

	QueuePtr p;
	if(Q->front == Q->rear)
		return ERROR;
	p = Q->front->next;
	*e = p->data;
	Q->front->next = p->next;
	if(Q->rear == p)
		Q->rear = Q->front;
	free(p);
	return OK;
}

Status QueueTraverse(LinkQueue *Q,void(*vi)(QElemType))
{
	/** 从队头到队尾依次对队列Q中每个元素调用函数vi(). **/

	QueuePtr p;
	p = Q->front->next;
	while(p)
	{
		vi(p->data);
		p=p->next;
	}
	printf("\n");
	return OK;
}


/***********************************队列结束********************************/

void ac_fail(tree* root)
{
	root->fail=NULL;
	LinkQueue *Q=(LinkQueue*)malloc( sizeof(LinkQueue) );
	InitQueue(&Q);
	EnQueue(Q,root);
	while(!QueueEmpty(Q))
	{
		int i;
		tree* now;
		/**GetHead(Q,&now);  
		  tree* now=Q.front();
		  printf("line = %d\n",__LINE__);  **/
		DeQueue(Q,&now);
		/*****Q.pop();    ***/
		for(i=0; i<TREEDATAMAX; i++)
			if(now->next[i])
			{
				tree* p=now->fail;
				while(p)
				{
					if(p->next[i])
					{
						now->next[i]->fail=p->next[i];
						break;
					}
					p=p->fail;
				}
				if(p==NULL)
				{
					now->next[i]->fail=root;
				}
				EnQueue(Q,now->next[i]);
				//Q.push(now->next[i]);
			}
	}
}
void insert(tree* next,char* p)
{
	unsigned char* s=(unsigned char*)p;
	const unsigned char *tmp = s;
	//strlen((const char *)s);
	while(*s)
	{
		if(next->next[*s]==NULL)next->next[*s]=make_tree();
		next=next->next[*s];
		s++;
	}
	if(next->cnt>0)return ;
	next->cnt++;
	next->s=(unsigned char *)malloc(strlen((const char *)tmp)+1);
	strcpy((char *)next->s,(const char*)tmp);
}
int ac_find(tree* root,char* p)
{
	int cnt = 0;
	unsigned char* s=(unsigned char*)p;
	tree* tem=root;
	while(*s)
	{
		//printf("%d ",(int)*s);
		while(tem->next[*s]==NULL&&tem!=root)tem=tem->fail;
		if(tem->next[*s]) tem=tem->next[*s];
		tree* p=tem;
		while(p)
		{
			//**            if(p->cnt)
		//	{
				//cnt+=p->cnt;   **/
				if(p->cnt)
				{
					printf("匹配到 %s\n",p->s);
				}
        //  }
				p=p->fail;
		}
		s++;
	}
	return cnt;
}



int main()
{
	tree* root=make_tree();
	insert(root,"she");
	insert(root,"she");
	insert(root,"he");
	insert(root,"e");
	insert(root,"哈尔滨工程大学");
	insert(root,"/");
	insert(root,"see");
	insert(root,"才5");
	printf("模式串为：she、/、才5、see\n");
	//	prinf();
	ac_fail(root);
	printf("主串为：lshe/天才555hk哈尔滨工程大学l\n");
	ac_find(root,"lshe/天才55hk哈尔滨工程大学l");
	return 0;
}

