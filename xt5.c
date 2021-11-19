/* 习题五 第一题*/
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
int main()
{	
	pid_t pid,pid_w;
	char buffer[100];//
	int fd;
	pid=fork(); /*此时已有两个进程在同时运行*/
	if (pid<0)			//若pid=-1创建子进程时报
	{
		printf("error in fork!\n");
	}
	else if (pid==0) /*返回0表示子进程*/
	{
		char s[]="201814570121+caohaiqing\n";
	//	printf("child process, PID is%d,n=%d\n",getpid(),n);
		fd=open("tmp.txt",O_RDWR|O_CREAT);	//以可读写方式打开文件，若不存在则创建
		if ( fd == -1 )				//若open()返回值为-1,则打开或创建失败
		{	 
			printf("Open or create file named \"temp.log\" failed.\n");
			return -1;
		}
		write(fd,s,sizeof(s));			//fd文件描述符，s为写入内容的内存缓存区地址，sizeof(s)写入字节数
		close(fd);            
		sleep(4);				//等待4秒
		exit(0);				//正常关闭
	}	
	else /*返回大于0表示父进程*/
	{
		sleep(1);				//等待子进程写入完内容
	//	printf("parent process, PID is%d,n=%d\n",getpid(),n);
		fd = open( "tmp.txt", O_RDONLY );	//只读方式打开文件
		if ( fd == -1 )
		{
			printf("Open file named \"temp.txt\" failed.\n");
			return -1;
		}
		/*读取文件内容保存到buffer指定的字符串数组中，返回读取的字符个数*/
		read( fd, buffer, sizeof(buffer) );
		close( fd );
		printf( "%s\n", buffer );
		
		do{
//			pid_w=wait(NULL);
//			pid_w=waitpid(pid,NULL,0);
			pid_w=waitpid(pid,NULL,WNOHANG);
			if(pid_w==0)
			{
			       	printf("Child process hasn't exited\n");
				sleep(1);
			}
		}
		while(pid_w==0);
		printf("Get child %d\n",pid_w);
	}
	return 0;
}

