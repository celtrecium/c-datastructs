CC=gcc
CFLAGS=-Iinclude -pedantic -Wall -Wextra -Wsign-conversion -Wconversion -Wshadow
OBJS=main.o bintree.o
SRC=src

all: options bintree.o main.o btdemo

options:
	@echo Binary Tree test build options:
	@echo "CC	= $(CC)"
	@echo "CFLAGS	= $(CFLAGS)"
	@echo

bintree.o: ${SRC}/bintree.c
	${CC} ${CFLAGS} -c $^

main.o: main.c
	${CC} ${CFLAGS} -c $^

btdemo: ${OBJS}
	${CC} ${CFLAGS} $^ -o $@
	rm -rf ${OBJS}
