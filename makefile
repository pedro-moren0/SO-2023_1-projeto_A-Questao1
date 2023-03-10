#Lazy makefile
CC=gcc
CFLAGS=-Wall
OBJS= main.o pqueue.o process.o mqp.o

main: $(OBJS)

$(OBJS): %.o: %.c

main.c:
	echo "int main() { return 0; }" > main.c

%.c:
	touch $@
