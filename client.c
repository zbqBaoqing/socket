//说明：套接口实现的客户端程序
//程序名：my_client.c
//编程时间：2012.7.31


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<errno.h>
#include<netinet/in.h>
#include<arpa/inet.h>


#define  BUFSIZE	1000			/*  */


#define	 PORT	4507			/*  */ 

void my_err(const char *err_string, int line)
{
	fprintf(stderr, "line: %d",line );
	perror(err_string);
	exit(1);
}


int main(int argc, char **argv)
{
	int		i;
	int		ret;
	int		conn_fd;
	int		serv_port;
	struct sockaddr_in  serv_addr;
	char		recv_buf[BUFSIZE];
	char	     send_buf[BUFSIZE];


	//检查参数的个数
	if (argc != 2)
	{
		printf("Usage:./a.out [serv_address]\n");
		exit(1);
	}

	//初始化服务器端的端口与地址
	memset(&serv_addr, 0, sizeof (struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
			
		//创建一个TCP套接字
	conn_fd = socket (AF_INET, SOCK_STREAM, 0);
	if (conn_fd < 0)
	{
		my_err("socket", __LINE__);
	}

	//向服务器端发送链接请求
	if (connect(conn_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) < 0)
	{
		my_err("connect", __LINE__);
	}

	while(1)
	{
	    printf("client: ");
	    scanf("%[^\n]",send_buf);
	  
	  if (send(conn_fd, send_buf, strlen(send_buf), 0) < 0)
	  {
		my_err("send", __LINE__);
	  }

	  bzero(send_buf, sizeof(send_buf));

	if((ret = recv(conn_fd, recv_buf, sizeof(recv_buf), 0)) < 0)
		{
			my_err("recv", __LINE__);
		}
	if (ret <= 0)
	{
		break;
	}
	recv_buf[ret]='\0';
	printf("server: %s\n",recv_buf);
	bzero(recv_buf, sizeof(recv_buf));
	getchar();  //消除缓冲区中的回车
	}
	

	close(conn_fd);
	return 0;
}
