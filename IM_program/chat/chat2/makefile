
OBJ=client.o cl_sock.o

server:server.c
	gcc -Wall server.c -o server -l pthread
client:client.o cl_sock.o client.h
	gcc -Wall $(OBJ) -o client `pkg-config gtk+-2.0 --libs` -l pthread
client.o:client.c client.h
	gcc -Wall -c $< `pkg-config gtk+-2.0 --cflags`
client_sock.o:cl_sock.c client.h
	gcc -Wall -c $<

clean:
	rm *.o
