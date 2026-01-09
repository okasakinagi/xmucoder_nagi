# Compiler settings for user-space programs
CC = gcc
CFLAGS = -Wall -g

.PHONY: all clean module

all: myshell mycommand

myshell: myshell.c
	$(CC) $(CFLAGS) myshell.c -o myshell -lreadline

mycommand: mycommand.c
	$(CC) $(CFLAGS) mycommand.c -o mycommand

clean:
	rm -f myshell mycommand
