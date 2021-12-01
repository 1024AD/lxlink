#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
void thread(void)
{
	int i,m;
	printf("新线程： ");
	for(i=10;i<30;i++)
	{	
		m = 0;
		if(i%5==3)
		{
			printf("%d ",i);
		}
	}
		printf("\n");
	m = 1;

//	int i;
//	for(i=0;i<3;i++)
//	printf("This is a pthread.\n");
}

int main(void)
{
	pthread_t tid;
	int ret,i;
	int m;
	char buffer[100]={"201814570121+caohaiqing"};

	ret = pthread_create(&tid,NULL,(void *) thread,NULL);
	if (ret != 0)
	{
		printf("pthread_create err!\n");
		return -1;
	}
/*	while(m != 1)
	{
		printf("m=%d",m);
		sleep(1);
		printf("sleep+1\n");
	}
*/
	sleep(1);
	printf("主线程： %s\n",buffer);
	


}
