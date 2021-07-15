CC=gcc
CFLAGS=-Iinclude -pedantic -Wall -Wextra -Wsign-conversion -Wconversion -Wshadow
OBJS=main.o hashtable.o htlinkedlist.o
SRC=src

all: options htlinkedlist.o hashtable.o main.o htdemo

options:
	@echo Hashtable test build options:
	@echo "CC	= $(CC)"
	@echo "CFLAGS	= $(CFLAGS)"
	@echo

htlinkedlist.o: ${SRC}/htlinkedlist.c
	${CC} ${CFLAGS} -c $^

hashtable.o: ${SRC}/hashtable.c
	${CC} ${CFLAGS} -c $^

main.o: main.c
	${CC} ${CFLAGS} -c $^

htdemo: ${OBJS}
	${CC} ${CFLAGS} $^ -o $@
	rm -rf ${OBJS}
