/*************************************************************************
    > File Name: point.c
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 2017年07月27日 星期四 19时10分20秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>
#include<stdlib.h>

#define CHAR "ssh-userauth"
#define ZL	"zl"


int main()
{

	char *p = "zl";
	printf("----> char *p = \"zl\" <----\n");
	printf("sizeof(*p) = %d\n", sizeof(*p));				
	printf("sizeof(p) = %d\n", sizeof(p));				
	printf("strlen(p) = %d\n", strlen(p));
	printf("\n\n");

	/* sizeof()求出来的字符串长度包括'\0' */
	char name[] = "zl";
	printf("----> char name[] = \"zl\" <----\n");
	printf("sizeof(name): %d\n", sizeof(name));
	printf("strlen(name): %d\n", strlen(name));
	printf("\n\n");

	printf("sizeof(\"ssh-userauth\") = %d\n", sizeof(CHAR));	
	printf("strlen(\"ssh-userauth\") = %d\n", strlen(CHAR));
	printf("\n");
	printf("sizeof(\"zl\") = %d\n", sizeof(ZL));		
	printf("strlen(\"zl\") = %d\n", strlen(ZL));
	printf("\n\n");

	printf("char类型大小为 %d 字节\n", sizeof(char));	
	printf("int类型大小为 %d 字节\n", sizeof(int));	
	printf("\n\n");

	return 0;
}

