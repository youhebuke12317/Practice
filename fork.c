/*************************************************************************
    > File Name: fork.c
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 2017年05月10日 星期三 22时17分09秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PROCESS_SIZE 4
struct Process {
	pid_t pid;
	int index;
};
struct Process *process;
int alive_process;

int spawn_child(int slot)
{
	int n;
	pid_t child;
	struct Process *p = process + slot;
	memset(p, 0, sizeof(struct Process));

	child = fork();
	if(child < 0)
	{
		printf("fork child error!\n");
		return -1;
	}
	else if(child == 0)
	{
		printf("[%d] child create success.\n", slot);
		while(1);
		 
		return 0;
	}
	else
	{
		p->index = slot;
		p->pid = child;

		return 1;
	}
}

int main(int argc, char *argv)
{
	int status;
	int ret, i = 0;
	alive_process = 0;

	process = malloc(PROCESS_SIZE * sizeof(struct Process));

	for(i = 0; i < PROCESS_SIZE; i++)
	{
		ret = spawn_child(i);
		if(ret == 0)
			return 0;
		else if(ret == 1)
			alive_process ++;
	}

	printf("\n");

	for(i = 0; i < PROCESS_SIZE; i++) {
		printf("[%d] process->pid: %d\n", process[i].index, process[i].pid);
	}

	sleep(2);
	printf("\nalive_process: %d\n", alive_process);

#if 1
	// 僵尸进程的处理  是否还有更好的方法
	for(i = 0; i < PROCESS_SIZE; i++) {
		waitpid(process[i].pid, NULL, 0);
	}
#endif

	return 0;
}
