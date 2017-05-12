/*******************************************************************
 ** Copyright(c) 2016,哈尔滨工程大学信息安全研究中心
 ** All rights reserved
 ** 
 ** 文件名: AC.c
 ** 创建人: zhengli
 ** 描  述: 参考穆***自动机进行整理
 ** 注  意: 
 ** 
 ** 当前版本：v1.0
 ** 作    者：zhengli
 ** 邮    箱: 
 ** 创建时间: 2016年12月09日 星期五 08时00分10秒
 ** 完成日期: 
 ******************************************************************/ 


#include	"Queue.h"
#include	"AC.h"

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
		//	if(p->cnt)
		//	{
		//		cnt+=p->cnt;
		//		if(p->cnt)
		//		{
		//			printf("匹配到 %s\n",p->s);
		//		}
		//	}
		//	p=p->fail;


			if(p->cnt)
			{
				printf("匹配到 %s\n",p->s);
			}
			p=p->fail;
		}
		s++;
	}
	return cnt;
}


#if 1
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

#endif
