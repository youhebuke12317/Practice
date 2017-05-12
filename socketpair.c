/*************************************************************************
    > File Name: socketpair.c
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 2017年05月10日 星期三 20时29分28秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

#define BUF_SIZE 32

int my_socketpair();
int my_socketpair_fork();

int main(int argc, char **argv)
{
	if(argc == 2)
	{
		if(argv[1] = 0)
			my_socketpair();
		else
			my_socketpair_fork();
	}
	else
		printf("参数格式: %s 0 或 %s 1\n", argv[0], argv[0]);
}

int my_socketpair()
{
	int w, r;
	int channel[2];	

	char * string = "This is a test string"; 
	char * buf = (char*)calloc(1 , BUF_SIZE);
	
	/*
	 * socketpair创建了一对无名的套接字描述符（只能在AF_UNIX域中使用），
	 * 描述符存储于一个二元数组,eg. channel[2] .
	 */
	if(socketpair(AF_UNIX, SOCK_STREAM, 0, channel) < 0)
	{
		perror("socketpair ERROR: ");
		return -1;
	}

	/* 
 	 * 这对套接字可以进行双工通信,每一个描述符既可以读也可以写。
 	 * 这个在同一个进程中也可以进行通信，向channel[0]中写入，就
 	 * 可以从s[1]中读取（只能从s[1]中读取），也可以在s[1]中写入，
 	 * 然后从s[0]中读取
 	 */
	// write
	if(( w = write(channel[0] , string , strlen(string) )) == -1 )
	{
		printf("Write socket error:%s\n",strerror(errno)); 
		return -1; 
	}

	// read 
	if((r = read(channel[1], buf , BUF_SIZE )) == -1)
	{
		printf("Read from socket error:%s\n",strerror(errno) ); 
		return -1; 
	}

	printf("[0 --> 1] Read string in same process : %s\n", buf); 

#if 1
	/* 
  	 * 但是，若没有在0端写入，而从1端读取，则1端的读取操作会阻塞，
  	 * 即使在1端写入，也不能从1读取，仍然阻塞；反之亦然......
  	 * */
	if((r = read(channel[0], buf , BUF_SIZE )) == -1)
	{
		printf("Read from socket s0 error:%s\n",strerror(errno) ); 
		return -1; 
	} 
	printf("[1 --> 0] Read from s0 :%s\n", buf); 
#endif

	printf("Test successed\n"); 
	return 0;
}


int my_socketpair_fork()
{
	int w, r; 
	int channel[2]; 
	pid_t pid; 

	char * string = "This is a test string"; 
	char * buf = (char*)calloc(1 , BUF_SIZE); 

	if( socketpair(AF_UNIX, SOCK_STREAM, 0, channel) == -1 )
	{
		printf("create unnamed socket pair failed:%s\n",strerror(errno) ); 
		exit(-1); 
	} 

	pid = fork();
	if(pid < 0)
	{
		printf("Fork failed:%s\n",strerror(errno)); 
		return -1;

	} else if (pid == 0) {	//子进程 s[0]可用
		printf("Parent process's pid is %d\n",getpid()); 
		close(channel[1]);

		if((w = write(channel[0] , string , strlen(string))) == -1) {
			printf("Write socket error:%s\n",strerror(errno)); 
			exit(-1); 
		} 

	} else {	//父进程 s[1]可用
		printf("Child process's pid is :%d\n",getpid()); 
		close(channel[0]); 

		if((r = read(channel[1], buf , BUF_SIZE)) == -1) {
			printf("Pid %d read from socket error:%s\n",getpid(), strerror(errno) ); 
			exit(-1); 
		} 

		printf("Pid %d read string in same process : %s \n", getpid(), buf); 
	}


	sleep(5);
	printf("Test successed, %d\n",getpid()); 
	exit(0); 
}
