CC=g++

compile : server client
server: server.o
	$(CC) -o server server.cpp -lpthread
client: client.o
	$(CC) -o client client.cpp
server.o:server.cpp
	$(CC) -c server.cpp
client.o: client.cpp
	$(CC) -c client.cpp
clean :
	rm server client *.o

