server:wrap.c epoll_server.c
	gcc -g -Wall wrap.c epoll_server.c  -o server
client:wrap.c client.c
	gcc -g -Wall wrap.c client.c -o client 

clean:
	-rm -f client server
