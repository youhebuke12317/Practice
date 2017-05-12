/*************************************************************************
    > File Name: libevent_model.c
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 2017年05月11日 星期四 19时54分12秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

struct Model {
	char *name;
	int	 index;
	int (*point_fun)(char *a, int b);
};

/****************************************************************/
int model_point_fun(char *a, int b);

struct Model model = {
	"model",
	10,
	model_point_fun
};

int model_point_fun(char *a, int b)
{
	printf("[%s %d] model_point_fun start...a: %s, b: %d\n", __FILE__, __LINE__, a, b);

	return 0;
}
/****************************************************************/

/****************************************************************/
typedef struct _TEST {
	int count;
	
	int (*test_fun)(int b);
}TEST;

int test_handel(char index)
{
	printf("[%s %d] test_handel index: %d\n", __FILE__, __LINE__, index);

	return 0;
}
/****************************************************************/


int main(int argc, char **argv)
{
	char *p = model.name;
	int num = model.index;

	printf("[%s %d] name: %s, index: %d\n", __FILE__, __LINE__, p, num);

	model.point_fun("123", 1);


	TEST *test = (TEST*)malloc(sizeof(TEST));
	test->count = 1;
	// 会出现警告 ???
	test->test_fun = test_handel;

	test->test_fun(test->count);

	return 0;
}
