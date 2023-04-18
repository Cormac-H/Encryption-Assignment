CC = gcc
CFLAGS = -Wall -Werror -ansi -lm

main.out: main.o
	$(CC) $(CFLAGS) -o main.out main.o

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

clean:
	rm main.out main.o
