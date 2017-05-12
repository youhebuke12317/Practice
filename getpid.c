/*************************************************************************
    > File Name: getpid.c
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 2017年05月10日 星期三 17时35分30秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv)
{
	char command[128];

	int ret = getpid();
	printf("self_pid: %d\n", ret);

	strcpy(command, "ps | grep -rn ");
	strcat(command, argv[0] + 2);

	//printf("%s\n", command);
	printf("\n");
	system(command);
	
	return 0;
}
