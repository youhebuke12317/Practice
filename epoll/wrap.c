/*
 * =====================================================================================
 *
 *       Filename:  wrap.c
 *
 *    Description:  �������װ����
 *
 *        Version:  1.0
 *        Created:  2016��10��15�� 10ʱ10��37��
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *   Organization:  
 *
 * =====================================================================================
 */

#include    <stdlib.h>
#include    <errno.h>
#include    <sys/socket.h>
#include    <stdio.h>
#include    <unistd.h>
#include    <sys/epoll.h>
#include    "wrap.h"

void
perr_exit(const char *s)
{
    perror(s);
    exit(1); 
}

int
Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
    int n = 0;

again:
    if((n = accept(fd, sa, salenptr)) < 0)
    {
        if((errno == ECONNABORTED) || (errno == EINTR))
            goto    again;
        else
            perr_exit("accept error");
    }
    return n;
}

void
Bind(int fd, struct sockaddr *sa, socklen_t salen)
{
    if(bind(fd, sa, salen) < 0)
        perr_exit("bind error");
}

void            
Connect(int fd, struct sockaddr *sa, socklen_t salen)
{
    if(connect(fd, sa, salen) < 0)
      perr_exit("connection error");
}

void            
Listen(int fd, int backlog)
{
    if(listen(fd, backlog) < 0)
      perr_exit("listen error");
}

int
Socket(int family, int type, int protocol)
{
    int n;

    if((n = socket(family, type, protocol)) < 0)
      perr_exit("socket error");
    return n;
}

void 
Close(int fd)
{
    if(close(fd) < 0)
      perr_exit("close error");
}

ssize_t 
my_read(int fd, char *ptr)
{
    static  int     read_cnt;
    static  char    *read_ptr;
    static  char    read_buf[100];

    if(read_cnt <= 0)
    {

again:
        if((read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0)
        {
            if(errno == EINTR)
              goto  again;
            return -1;
        }
        else if(read_cnt == 0)
          return 0;
        read_ptr = read_buf;
    }
    read_cnt--;
    *ptr = *read_ptr++;
    return 1;
}

ssize_t
Read(int fd, void *ptr, size_t nbytes)
{
    ssize_t n;

again:
    if((n = read(fd, ptr, nbytes)) == -1)
    {
        //��ֹreadʱ���жϴ��
        if(errno == EINTR)
          goto  again;
        else
          return -1;
    }
    return n;
}

ssize_t
Readn(int fd, void *vptr, size_t n)
{
    size_t  nleft;
    ssize_t nread;
    char    *ptr;

    ptr = vptr;
    nleft = n;

    while(nleft > 0)
    {
        if((nread = read(fd, vptr, n)) < 0)
        {
           if(errno == EINTR)
             nread = 0;
           else
             return -1;
        }
        else if(nread == 0)
          break;

        nleft -= nread;
        ptr += nread;
    }
    return  (n-nleft);

}

ssize_t   
Readline(int fd, void *vptr, size_t maxlen)
{
    ssize_t n, rc;
    char    c, *ptr;

    ptr = vptr;
    for(n = 1; n < maxlen; n++)
    {
        if((rc = my_read(fd, &c)) == 1)
        {
            *ptr++ = c;
            if((c == '\n'))
              break;
        }
        else if(rc == 0)
        {
            *ptr = 0;
            return n-1;
        }else
          return -1;
    }
    *ptr = 0;
    return  n;
}

ssize_t       
Write(int fd, const void *ptr, size_t nbytes)
{
    ssize_t n = 0;

again:
    if((write(fd, ptr, nbytes)) < 0)
    {
        //ͬRead������
        if(errno == EINTR)
          goto  again;
        else
          return -1;
    }
    return n;
}

ssize_t
Writen(int fd, const void *vptr, size_t n)
{
    size_t  nleft;
    ssize_t nwritten;
    const char  *ptr;

    ptr = vptr;
    nleft = n;

    while(nleft > 0)
    {
        if((nwritten = write(fd, vptr, nleft)) < 0)
        {
            if(nwritten < 0 && errno == EINTR)
              nwritten = 0;
            else
              return -1;
        }

        nleft -= nwritten;
        ptr += nwritten;
    }
    return n;
}

int
Epoll_create(int size)
{
    int efd;
    if((efd = epoll_create(size))  == -1)
      perr_exit("Epoll_create error");
    return efd;
}

int
Epoll_ctl(int efd, int op, int fd, struct epoll_event *event)
{
    int res;
    if((res = epoll_ctl(efd, op, fd, event)) == -1)
        perr_exit("epoll_ctl error");
    return res;
}

int
Epoll_wait(int efd, struct epoll_event *events, int maxevents, int timeout)
{
    int nready;
    if((nready = epoll_wait(efd, events, maxevents, timeout)) == -1)
        perr_exit("epoll_wait error");
    return nready;
}
