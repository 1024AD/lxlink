/* fork_test.c */
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
main()
{
	pid_t pid; /*此时仅有一个进程*/
	int n=4;
	pid=fork(); /*此时已有两个进程在同时运行*/
	if (pid<0)
	printf("error in fork!\n");
	else if (pid==0) /*返回0表示子进程*/
	{
		n++;
		printf("child process, PID is%d,n=%d\n",getpid(),n);
	}	
	else /*返回大于0表示父进程*/
	{
		n--;
		printf("parent process, PID is%d,n=%d\n",getpid(),n);
	}
}
