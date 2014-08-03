  /*
  * =====================================================================================
  *
  *       Filename:  client.c
  *
  *    	 Description:  多进程并发服务器的client端程序
  *
  *       Version:  1.0
  *       Created:  2014年07月17日 10时18分16秒
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
  #include<string.h>
  #include<stdlib.h>
  #include<unistd.h>
  #include<sys/types.h>
  #include<sys/socket.h>
  #include<string.h>
  #include<errno.h>
  #include<netinet/in.h>
  #include<arpa/inet.h>
  #include<netdb.h>

#define	BUFSIZE	200			/*  */

  #define SERV_PORT    4507     //服务器端的端口


  void my_err(const char * err_string, int err_line)
  {
	  fprintf(stderr,"%d",err_line);
	  perror(err_string);
	  exit(1);
  }

  int main(int argc, char **argv)
  {
	  int		i;
	  int		ret;
	  int		sock_fd;
	  struct sockaddr_in  serv_addr;
	  struct hostent *he;
	  char recv_buf[BUFSIZE]={'\0'},send_buf[BUFSIZE]={'\0'};


	  //检查参数的个数
	  if (argc != 2)
	  {
		  printf("Usage: %s [serv_address]\n",argv[0]);
		  exit(1);
	  }
	  if ((he=gethostbyname(argv[1])) == NULL)
	  {
		  printf("gethostbyname() error\n");
		  exit(1);
	  }
	  //创建一个TCP套接字
	  sock_fd = socket (AF_INET, SOCK_STREAM, 0);
	  if (sock_fd < 0)
	  {
		  my_err("socket", __LINE__);
	  }

	  //初始化服务器端的端口与地址
	  memset(&serv_addr, 0, sizeof (struct sockaddr_in));
	  serv_addr.sin_family = AF_INET;
	  serv_addr.sin_port = htons(SERV_PORT);
	  serv_addr.sin_addr = *((struct in_addr *)he->h_addr);


	  
	  //向服务器端发送链接请求
	  if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) < 0)
	  {
		  my_err("connect", __LINE__);
	  }
  while(1)
	{
	    printf("client: ");
	    scanf("%[^\n]",send_buf);
	  
	  if (send(sock_fd, send_buf, strlen(send_buf), 0) < 0)
	  {
		my_err("send", __LINE__);
	  }

	  bzero(send_buf, sizeof(send_buf));

	if((ret = recv(sock_fd, recv_buf, sizeof(recv_buf), 0)) < 0)
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
	  close(sock_fd);
	  return 0;
  }


