/*******************************************************************
 ** Copyright(c) 2016,哈尔滨工程大学信息安全研究中心
 ** All rights reserved
 ** 
 ** 文件名: AC_List.h
 ** 创建人: zhengli
 ** 描  述: 
 ** 注  意: 
 ** 
 ** 当前版本：v1.0
 ** 作    者：zhengli
 ** 邮    箱: 
 ** 创建时间: 2016年12月09日 星期五 08时15分44秒
 ** 完成日期: 
 ******************************************************************/ 

#ifndef __AC_LIST_H_
#define __AC_LIST_H_

#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	"AC.h"

#define OVERFLOW -1
#define OK 0
#define TRUE 1
#define FALSE 0
#define ERROR -1024

typedef tree* QElemType;
typedef int Status;

typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}*QueuePtr;

typedef struct Queue
{
	QueuePtr front,rear; /***对头队尾指针***/

} LinkQueue;


	/**构造一个空队列***/
Status InitQueue(LinkQueue **Q);
	/**销毁队列Q  ***/
Status DestroyQueue(LinkQueue *Q);
	/***将Q清为空***/
Status ClearQueue(LinkQueue *Q);
	/***若Q为空队列，则返回TRUE，否则返回FALSE **/
Status QueueEmpty(LinkQueue *Q);
	/**求队列的长度**/
int QueueLength(LinkQueue *Q);
	/**若队列不空，用e返回Q的队头元素，并返回OK ，否则返回ERROR; **/
Status GetHead(LinkQueue *Q,QElemType *e);
	/**插入元素e为Q的新的队尾元素**/
Status EnQueue(LinkQueue *Q,QElemType e);
	/**若队列不空，删除Q的队头元素，用e返回其值，并返回OK，否则返回ERROR  **/
Status DeQueue(LinkQueue *Q,QElemType *e);
	/** 从队头到队尾依次对队列Q中每个元素调用函数vi(). **/
Status QueueTraverse(LinkQueue *Q,void(*vi)(QElemType));


#endif
