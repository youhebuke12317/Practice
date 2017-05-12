#include    <stdio.h>
#include    <stdlib.h>
#include    <sys/socket.h>
#include    <sys/types.h>
#include    <ctype.h>
#include    <arpa/inet.h>
#include    <string.h>
#include    <sys/epoll.h>
#include    <unistd.h>
#include    <error.h>
#include    "wrap.h"


#define     MAXLINE     80
#define     SERV_PORT   8000
#define     OPEN_MAX    1024
#define     SA          struct sockaddr     


int
main(int argc, char *argv[])
{
	int         i, j, listenfd, connfd, sockfd;
	int         nready, efd;
	int 		maxi = 1000;
	ssize_t     n;
	char        buf[MAXLINE], str[INET_ADDRSTRLEN];
	socklen_t   clilen;
//	int         client[OPEN_MAX];
	struct sockaddr_in  servaddr, cliaddr;
	struct epoll_event  tep, ep[OPEN_MAX];
    
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int opt = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	Bind(listenfd, (SA*) &servaddr, sizeof(servaddr));

	Listen(listenfd, 20);

	efd = Epoll_create(OPEN_MAX);

	tep.events = EPOLLIN;
	tep.data.fd = listenfd;
	Epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &tep);

	while(1)
	{
		nready = Epoll_wait(efd, ep, maxi, -1);
		for(i = 0; i < nready; i++)
        {
			if(!(ep[i].events & EPOLLIN))
				continue;
            if(ep[i].data.fd == listenfd)
            {
                clilen = sizeof(cliaddr);
				printf("sdsdsd\n");
                connfd = Accept(listenfd, (SA*) &cliaddr, &clilen);

				printf("receive from %s at PORT %d\n", 
                            inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), 
							ntohs(cliaddr.sin_port));
                
				tep.events = EPOLLIN;
                tep.data.fd = connfd;
				Epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &tep);

				continue;
            }

			sockfd = ep[i].data.fd;
			n = Read(sockfd, buf, MAXLINE);

			if(n == 0)
			{
				Epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);
				Close(sockfd);
				printf("client[%d] close connection\n", j);
				continue;
			}
			for(j = 0; j < n; j++)
				buf[j] = toupper(buf[j]);

			Writen(STDOUT_FILENO, buf, n);
			Writen(sockfd, buf, n);
		}
	}
	Close(listenfd);
	close(efd);
    return 0;
}
