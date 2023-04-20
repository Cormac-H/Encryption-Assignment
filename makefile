CC = gcc
CFLAGS = -Wall -Werror -ansi -lm

main.out: main.o encrypt.o
	$(CC) $(CFLAGS) -o main.out main.o encrypt.o

main.o: main.c encrypt.h
	$(CC) $(CFLAGS) -c -o main.o main.c

encrypt.o: encrypt.c encrypt.h
	$(CC) $(CFLAGS) -c -o encrypt.o encrypt.c

clean:
	rm main.out main.o encrypt.o
