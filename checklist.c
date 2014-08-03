/*
 * =====================================================================================
 *
 *       Filename:  checklist.c
 *
 *    	 Description:  查看主机的字节序
 *
 *       Version:  1.0
 *       Created:  2014年08月03日 18时35分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *	     CopyRight: open , free , share
 *       Author:  yexingkong(zhangbaoqing)
 *	     Email: abqyexingkong@gmail.com
 *       Company:  Xi'an University of post and Telecommunications
 *
 * =====================================================================================
 */


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
int i = 0;

union {
        int value;
        char ch[sizeof(int)];
    }test;

    test.value = 0x04030201;

    for (i = 0;i < sizeof(int); i++)
    {
        printf("%p --> %#x\n",&test.ch[i],test.ch[i] );
    }
    printf("\n");


    return EXIT_SUCCESS;
}



