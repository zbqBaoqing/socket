/*
 * =====================================================================================
 *
 *       Filename:  server.c
 *
 *    	 Description:  多进程并发服务器的server端程序
 *
 *       Version:  1.0
 *       Created:  2014年07月17日 09时45分30秒
 *       Revision:  none
 *       Compiler:  gcc
 *	     CopyRight: open , free , share
 *       Author:  yexingkong(zhangbaoqing)
 *	     Email: abqyexingkong@gmail.com
 *       Company:  Xi'an University of post and Telecommunications
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



#define SERV_PORT	4507 //服务端的端口
#define LISTENQ		12  //链接请求队列的最大长度

#define	BUFSIZE  200		/*  */

void my_err(const char *err_string, int err_line)
{
	fprintf(stderr,"line: %d",err_line);
	perror(err_string);
	exit(1);
}


int main()
{
	int		sock_fd,conn_fd;
	int		optval;
	int		ret;
	int		name_num;
	pid_t		pid;
	socklen_t	cli_len;
	struct sockaddr_in  cli_addr,serv_addr;
	char	recv_buf[BUFSIZE]={'\0'}, send_buf[BUFSIZE]={'\0'};

	//创建一个TCPT套接字
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	{
		if(sock_fd < 0)
		{
			my_err("socket", __LINE__);
		}
	}

	//设置该套接字使之可以重新绑定端口
	optval = 1;
	if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) < 0)
	{
		my_err("setsockopt", __LINE__);
	}


	//初始化服务端地址结构
	memset(&serv_addr, 0 , sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin_addr.s_addr = htons(INADDR_ANY);


	//将套接字绑定到本地端口
	if(bind(sock_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in)) < 0)
	{
		my_err("bind", __LINE__);
	}

	//将套接字转化为监听套接字
	if(listen(sock_fd, LISTENQ))
	{
		my_err("listen", __LINE__);
	}

	cli_len = sizeof(struct sockaddr_in);
	while(1)
	{
		//通过accept接收客户端的链接请求，并返回链接套接字
		conn_fd = accept(sock_fd, (struct sockaddr *)&cli_addr, &cli_len);
		if(conn_fd < 0)
		{
			my_err("accept", __LINE__);
		}

		printf("accept a new client , ip: %s\n", inet_ntoa(cli_addr.sin_addr));

		//创建一个子进程处理刚刚接收的链接请求
		if((pid = fork()) == 0)
		{
			close(sock_fd);    //子进程关闭监听描述符
			while(1)
			{

			if((ret = recv(conn_fd, recv_buf, sizeof(recv_buf), 0)) < 0)
				{
					my_err("recv", __LINE__);
					perror("recv");
					exit(1);
				}
				if (ret <= 0)
		 		 break;
				recv_buf[ret] = '\0'; //将数据结束标志'\n'替换成字符串标志
					printf("client: %s\n", recv_buf);
					bzero(recv_buf,sizeof(recv_buf));
			
					printf("server: ");
			      scanf("%[^\n]",send_buf);
			      if(send(conn_fd, send_buf, strlen(send_buf), 0) < 0)
			      {
				  my_err("send", __LINE__); //my_err函数在my_recv.h中声明
			      }
				  bzero(send_buf,sizeof(send_buf));
				getchar(); //消除缓冲区中回车符

		}
			exit(0); //结束子进程
		}else if(pid > 0)	//父进程关闭刚刚接收的链接请求，执行accept等待其他链接请求
		{
				close(conn_fd); //父进程关闭已连接描述符
		        continue;
		}
	else {
			printf("fork() error\n");
			exit(1);
		}
	}
	close(sock_fd);
	return 0;
}

