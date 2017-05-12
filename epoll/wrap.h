/*
 * =====================================================================================
 *
 *       Filename:  wrap.h
 *
 *    Description:  �������װ����ͷ�ļ�
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


#ifndef __WRAP_H_
#define __WRAP_H_

void            perr_exit(const char *s);
int             Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
void            Bind(int fd, struct sockaddr *sa, socklen_t salen);
void            Connect(int fd, struct sockaddr *sa, socklen_t salen);
void            Listen(int fd, int backlog);
int             Socket(int family, int type, int protocol);
void            Close(int fd);

ssize_t			my_read(int fd, char *ptr);
ssize_t         Read(int fd, void *ptr, size_t nbytes);
ssize_t         Readn(int fd, void *vptr, size_t n);
ssize_t         Readline(int fd, void *vptr, size_t maxlen);

ssize_t         Write(int fd, const void *ptr, size_t nbytes);
ssize_t         Writen(int fd, const void *vptr, size_t nbytes);


int
Epoll_create(int size);

int
Epoll_ctl(int efd, int op, int fd, 
            struct epoll_event *event);
int
Epoll_wait(int epfd, struct epoll_event *events,
            int maxevents, int timeout);

#endif
