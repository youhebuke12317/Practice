/*************************************************************************
    > File Name: signal.c
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 2017年05月11日 星期四 14时40分05秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <signal.h>

/*************************************************************************
 * typedef void (*sighandler_t)(int);
 *
 * sighandler_t signal(int signum, sighandler_t handler);
 *
 * 第一个参数signum：指明了所要处理的信号类型，它可以取除了SIGKILL和SIGSTOP外的任何一种信号。 　 
 *		命令kill -l可以查看如下信号： 
 *			   1) SIGHUP	 2) SIGINT	 3) SIGQUIT		 4) SIGILL	 5) SIGTRAP
 *			   6) SIGABRT	 7) SIGBUS	 8) SIGFPE		 9) SIGKILL	10) SIGUSR1
 *			  11) SIGSEGV	12) SIGUSR2	13) SIGPIPE		14) SIGALRM	15) SIGTERM
 *			  16) SIGSTKFLT	17) SIGCHLD	18) SIGCONT		19) SIGSTOP	20) SIGTSTP
 *			  21) SIGTTIN	22) SIGTTOU	23) SIGURG		24) SIGXCPU	25) SIGXFSZ
 *			  26) SIGVTALRM	27) SIGPROF	28) SIGWINCH	29) SIGIO	30) SIGPWR
 *
 *			  31) SIGSYS	34) SIGRTMIN	35) SIGRTMIN+1	36) SIGRTMIN+2	37) SIGRTMIN+3
 *			  38) SIGRTMIN+4	39) SIGRTMIN+5	40) SIGRTMIN+6	41) SIGRTMIN+7	42) SIGRTMIN+8
 *			  43) SIGRTMIN+9	44) SIGRTMIN+10	45) SIGRTMIN+11	46) SIGRTMIN+12	47) SIGRTMIN+13
 *			  48) SIGRTMIN+14	49) SIGRTMIN+15	50) SIGRTMAX-14	51) SIGRTMAX-13	52) SIGRTMAX-12
 *			  53) SIGRTMAX-11	54) SIGRTMAX-10	55) SIGRTMAX-9	56) SIGRTMAX-8	57) SIGRTMAX-7
 *			  58) SIGRTMAX-6	59) SIGRTMAX-5	60) SIGRTMAX-4	61) SIGRTMAX-3	62) SIGRTMAX-2
 *			  63) SIGRTMAX-1	64) SIGRTMAX
 *
 * 第二个参数handler：描述了与信号关联的动作，它可以取以下三种值： 
 *			(1) SIG_IGN		这个符号表示忽略该信号
 *			(2) SIG_DFL		这个符号表示恢复对信号的系统默认处理。不写此处理函数默认也是执行系统默认操作
 *			(3) sighandler_t类型的函数指针 
 *
 **************************************************************************/

typedef void (*sighandler_t)(int);

void signal_hander_fun(int signum);

int main(int argc, char **argv)
{
	int num;
	if(argc == 2)
	{
		num = atoi(argv[1]);

		if(num == 0)
			signal(SIGINT, SIG_IGN);
		else if(num == 1)
			signal(SIGINT, SIG_DFL);
		else
			signal(SIGINT, signal_hander_fun);

		while(1);
	}
	else {
		printf("参数格式不正确，请重新输入[%s 0 或 %s 1 或 %s 2]\n", argv[0], argv[0], argv[0]);
		printf("	0代表测试signal函数处理忽略该信息\n");
		printf("	1代表测试signal函数采用系统默认操作处理该信息\n");
		printf("	2代表测试signal函数采用自定义处理方式处理该信息\n");
	}

	return 0;
}


void signal_hander_fun(int signum)
{
	printf("catch signal %d\n", signum);
}



#if 0

SIGHUP		发送给具有Terminal的Controlling Process，当terminal 被disconnect时候发送
SIGINT		由Interrupt Key产生，通常是CTRL+C或者DELETE。发送给所有ForeGround Group的进程
SIGQUIT		输入Quit Key的时候（CTRL+\）发送给所有Foreground Group的进程
SIGILL		非法指令异常
SIGTRAP		实现相关的硬件异常。一般是调试异常

SIGABRT		由调用abort函数产生，进程非正常退出
SIGBUS		某种特定的硬件异常，通常由内存访问引起
SIGFPE		数学相关的异常，如被0除，浮点溢出，等等
SIGKILL		无法处理和忽略。中止某个进程
SIGUSR1		用户自定义signal 1

SIGSEGV		非法内存访问
SIGUSR2		用户自定义signal 2
SIGPIPE		在reader中止之后写Pipe的时候发送
SIGALRM		用alarm函数设置的timer超时或setitimer函数设置的interval timer超时
SIGTERM		请求中止进程，kill命令缺省发送

SIGSTKFLT	Linux专用，数学协处理器的栈异常
SIGCHLD		进程Terminate或Stop的时候，SIGCHLD会发送给它的父进程。缺省情况下该Signal会被忽略
SIGCONT		当被stop的进程恢复运行的时候，自动发送
SIGSTOP		中止进程。无法处理和忽略。
SIGTSTP		Suspend Key，一般是Ctrl+Z。发送给所有Foreground Group的进程

SIGTTIN		当Background Group的进程尝试读取Terminal的时候发送
SIGTTOU		当Background Group的进程尝试写Terminal的时候发送
SIGURG		当out-of-band data接收的时候可能发送
SIGXCPU		当CPU时间限制超时的时候
SIGXFSZ		进程超过文件大小限制

SIGVTALRM	setitimer函数设置的Virtual Interval Timer超时的时候
SIGPROF		Setitimer指定的Profiling Interval Timer所产生
SIGWINCH	当Terminal的窗口大小改变的时候，发送给Foreground Group的所有进程
SIGIO		异步IO事件
SIGPWR		和系统相关。和UPS相关。

SIGSYS		非法系统调用

SIGCANCEL	由Solaris Thread Library内部使用，通常不会使用
SIGEMT		和实现相关的硬件异常
SIGFREEZE	Solaris专用，Hiberate或者Suspended时候发送
SIGINFO		BSD signal。由Status Key产生，通常是CTRL+T。发送给所有Foreground Group的进程
SIGIOT		实现相关的硬件异常，一般对应SIGABRT
SIGLWP		由Solaris Thread Libray内部使用
SIGPOLL		当某个事件发送给Pollable Device的时候发送
SIGTHAW		Solaris专用，从Suspend恢复时候发送
SIGWAITING	Solaris Thread Library内部实现专用
SIGXRES		Solaris专用，进程超过资源限制的时候发

#endif
