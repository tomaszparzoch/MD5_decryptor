CC = gcc

all: threads.o func.o data.o main.o
	$(CC) threads.o func.o data.o main.o -o sys9 -lcrypto -lssl -pthread

threads.o: threads.c threads.h
	$(CC) threads.c -c -o threads.o
func.o: func.c func.h
	$(CC) func.c -c -o func.o
data.o: data.c data.h
	$(CC) data.c -c -o data.o
main.o: main.c
	$(CC) main.c -c -o main.o

clean:
	rm -f *.o

