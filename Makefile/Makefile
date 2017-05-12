#########################################
CFLAGS = -c -g -Wall
LDFLAGS = 
CPPFLAGS = -I./
CC = gcc

#当前目录下所有的.c文件
src = $(wildcard *.c)
#将当前目录下文件.c 文件换成.o 文件
obj = $(patsubst %.c,%.o, $(src))
target = app


$(target):$(obj)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@

#当前目录下有clean文件时，make clean不能执行，但是加上.PHONY时可以正常执行
#伪目标
.PHONY:clean
clean:
	-rm -f $(target) $(obj)

abc:
	@echo $(src)
	@echo $(obj)



