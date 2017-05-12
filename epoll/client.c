/*
 * =====================================================================================
 *
 *       Filename:  test_poll_cli.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016Äê10ÔÂ18ÈÕ 13Ê±19·Ö31Ãë
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author: 
 *   Organization:  
 *
 * =====================================================================================
 */

#include    <stdio.h>
#include    <stdlib.h>
#include    <unistd.h>
#include    <netinet/in.h>
#include    <sys/socket.h>
#include    <sys/types.h>
#include    <strings.h>
#include    <string.h>
#define     MAXLINE 80
#define     SERV_PORT   8000
#define     SA      struct sockaddr
int
main(int argc, char *argv[])
{
    struct      sockaddr_in servaddr;
    int         sockfd, n;
    char        buf[MAXLINE];

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    Connect(sockfd, (SA*) &servaddr, sizeof(servaddr));

    while(fgets(buf, MAXLINE, stdin) != NULL)
    {
        Write(sockfd, buf, strlen(buf));
		n = Read(sockfd, buf, MAXLINE);
		if(n == 0)
            printf("the other side has been close.\n");
        else
            Write(STDOUT_FILENO, buf, n);
    }
    Close(sockfd);
    return 0;
}

