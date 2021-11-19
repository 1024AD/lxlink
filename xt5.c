/* 习题五 第一题*/
#include<stdio.h>
#include<sys/types.h>	/*提供pid_t类型的定义*/
#include<unistd.h>	/*提供ssize_t类型的定义 read write */ /*提供fork()函数定义*/
#include<sys/wait.h>	
#include<sys/stat.h>	/*提供mode_t类型的定义 open()中*/
#include<stdlib.h>	/*定义exit()h函数*/
#include<fcntl.h>	/*声明调用open()时的flag常量*/
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
		if ( fd == -1 )				//判断是否打开成功
		{
			printf("Open file named \"temp.txt\" failed.\n");
			return -1;
		}
		/*读取文件内容保存到buffer指定的字符串数组中，返回读取的字符个数*/
		read( fd, buffer, sizeof(buffer) );
		close( fd );
		printf( "%s\n", buffer );
		
		do{					//
//			pid_w=wait(NULL);
//			pid_w=waitpid(pid,NULL,0);
			pid_w=waitpid(pid,NULL,WNOHANG);//加入WNOHANG选项，正常调用并清理掉返回子进程pid，子程序正在运行返回0,调用失败返回-1
			if(pid_w==0)			//判断子程序是否在运行，如果运行输出“",并等待1s
			{
			       	printf("Child process hasn't exited\n");
				sleep(1);
			}
		}
		while(pid_w==0);
		printf("Get child %d\n",pid_w);		//输出清理掉的子程序的pid
	}
	return 0;
}

