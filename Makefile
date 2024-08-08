CC = gcc
CFLAGS = -Wall -pthread

all: projeto

projeto: projeto.c
	$(CC) $(CFLAGS) -o projeto projeto.c

clean:
	rm -f projeto

