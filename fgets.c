/*************************************************************************
    > File Name: fgets.c
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 2017年05月10日 星期三 18时48分23秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

#define FILENAME "./test.txt"
#define LINESIZE 1024

int my_strlen(char const *string, int size)
{

	size_t length;
	for(length = 0; length < size; length ++) 
	{
		if(*string++ == '\0') {
			break;
		}   
	}   
	return length;
}

int main(int argc, char **argv)
{
	FILE *fp;
	char s[LINESIZE];

	fp = fopen(FILENAME, "r");

	while(fgets(s, LINESIZE, fp) != NULL)
	{
		if(s[0] == '#' || s[0] == '\r' || s[0] == '\t' || s[0] == '\n')                                        
			continue;
		printf("%s", s);
		printf("num: %d\n", my_strlen(s, LINESIZE));
	}
	printf("\n");

	return 0;
}
