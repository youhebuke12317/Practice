/*******************************************************************
 ** Copyright(c) 2016,哈尔滨工程大学信息安全研究中心
 ** All rights reserved
 ** 
 ** 文件名: AC.h
 ** 创建人: zhengli
 ** 描  述: 
 ** 注  意: 
 ** 
 ** 当前版本：v1.0
 ** 作    者：zhengli
 ** 邮    箱: 
 ** 创建时间: 2016年12月09日 星期五 08时19分38秒
 ** 完成日期: 
 ******************************************************************/ 

#ifndef __AC_H_
#define __AC_H_

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


#endif
