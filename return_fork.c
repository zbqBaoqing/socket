/*
 * =====================================================================================
 *
 *       Filename:  fork.c
 *
 *    	 Description:  创建进程练习,验证返回值
 *
 *       Version:  1.0
 *       Created:  2014年08月03日 17时15分59秒
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

	printf("Process Creation Study\n");
	pid = fork();
	switch(pid)
	{
		case 0:

		    printf("Child process is running,Child PID :%d\n, parent ID: %d\n",getpid(), getppid());
			break;
		case -1: 
			perror("process creation failed\n");
			break;
		default :
			printf("I am parent process, my pid is %d\n",getpid());
			break;
	}

	return 0;

}


