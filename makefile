CC = gcc
CFLAGS = -Wall -Werror -ansi -lm

main.out: main.o encrypt.o compress.o sort.o search.o menu.o
	$(CC) $(CFLAGS) -o main.out main.o encrypt.o compress.o sort.o search.o menu.o

main.o: main.c encrypt.h compress.h menu.h
	$(CC) $(CFLAGS) -c -o main.o main.c

encrypt.o: encrypt.c encrypt.h menu.h
	$(CC) $(CFLAGS) -c -o encrypt.o encrypt.c

compress.o: compress.c compress.h menu.h
	$(CC) $(CFLAGS) -c -o compress.o compress.c

sort.o: sort.c sort.h menu.h
	$(CC) $(CFLAGS) -c -o sort.o sort.c

search.o: search.c search.h menu.h
	$(CC) $(CFLAGS) -c -o search.o search.c

menu.o: menu.c menu.h
	$(CC) $(CFLAGS) -c -o menu.o menu.c
clean:
	rm main.out main.o encrypt.o compress.o sort.o search.o
