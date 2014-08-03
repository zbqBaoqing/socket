/*
 * =====================================================================================
 *
 *       Filename:  chilCpParefork.c
 *
 *    	 Description:  子进程复制父进程的资源
 *
 *       Version:  1.0
 *       Created:  2014年08月03日 17时56分18秒
 *       Revision:  none
 *       Compiler:  gcc
 *	     CopyRight: open , free , share
 *       Author:  yexingkong(zhangbaoqing)
 *	     Email: abqyexingkong@gmail.com
 *       Company:  Xi'an University of post and Telecommunications
 *
 * =====================================================================================
 */

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>


int main(int argc, char *argv[])
{
	pid_t	pid;
	int k = 3, i = 0;

	printf("Process Creation Study\n");
	pid = fork();
	switch(pid)
	{
		case 0:
	      
		    for(i = 0 ;i < 8; i++)
			k++;
		    printf("child process, k= %d\n",k);
			break;
		case -1: 
			perror("process creation failed\n");
			break;
		default :
		      for(i = 0 ;i < 3; i++)
			k++;
		    printf("parent process, k= %d\n",k);
			break;
	}

	return 0;

}



