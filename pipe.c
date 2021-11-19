/*****习题5 题目2*******/
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/wait.h>
int main()
	{
	       	int fd[2], nbytes;
		pid_t childpid,pid_w;
		char string[] = "201814570121+caohaiqing\n";
		char readbuffer[80];
		if(pipe(fd)<0) /*创建管道*/
		{
		       	printf("创建失败\n");
			return -1;
	       	}
		if( (childpid = fork())== -1)
		{
		       	exit(1);	//子进程创建失败非正常推出	
	       	}
		if(childpid>0) /*父进程*/
		{
		       	close(fd[0]); /* 关闭读端 */
//			sleep(3);
			write(fd[1], string, strlen(string));/* 通过写端发送字符串 */
			close(fd[1]); /*关闭写端*/
  			do
			{					
				pid_w=waitpid(childpid,NULL,WNOHANG);//加入WNOHANG选项，正常调用并清理掉返回子进程pid，子程序正在运行返回0,调用失败返回-1
				if(pid_w==0)			//判断子程序是否在运行，如果运行输出,并等待1s
				{
				       	printf("Child process hasn't exited\n");
					sleep(1);
				}
			}
			while(pid_w==0);
			printf("Child process has exited\n");

		}	
		else if(childpid==0) /* 子进程*/
		{
			sleep(1);
		       	close(fd[1]); /* 关闭写端*/
			nbytes = read(fd[0], readbuffer,sizeof(readbuffer));/* 从管道中读取字符串 */
			printf("Received string: %s", readbuffer);
			close(fd[0]); /*关闭读端*/
			exit(0);
		}
		return(0);
}
