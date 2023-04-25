CC = gcc
CFLAGS = -Wall -Werror -ansi -lm

main.out: main.o encrypt.o compress.o sort.o search.o
	$(CC) $(CFLAGS) -o main.out main.o encrypt.o compress.o sort.o search.o

main.o: main.c encrypt.h
	$(CC) $(CFLAGS) -c -o main.o main.c

encrypt.o: encrypt.c encrypt.h
	$(CC) $(CFLAGS) -c -o encrypt.o encrypt.c

compress.o: compress.c compress.h
	$(CC) $(CFLAGS) -c -o compress.o compress.c

sort.o: sort.c sort.h
	$(CC) $(CFLAGS) -c -o sort.o sort.c

search.o: search.c search.h
	$(CC) $(CFLAGS) -c -o search.o search.c

menu.o: menu.c
	$(CC) $(CFLAGS) -c -o menu.o menu.c
clean:
	rm main.out main.o encrypt.o
