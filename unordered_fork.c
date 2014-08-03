/*
 * =====================================================================================
 *
 *       Filename:  unordered_fork.c
 *
 *    	 Description:  fork后，父子进程执行顺序不定
 *
 *       Version:  1.0
 *       Created:  2014年08月03日 17时29分12秒
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
	char	*msg;
	int	k;

	printf("Process Creation Study\n");
	pid = fork();
	switch(pid)
	{
		case 0:
			msg = "chile process is runing";
			k = 3;
			break;
		case -1: 
			perror("process creation failed\n");
			break;
		default :
			msg = "parent process is runing";
			k = 5;
			break;
	}
	while(k > 0)
	{
		puts(msg);
//		sleep(1); //父子进程交替执行
		k--;
	}

	return 0;
}


