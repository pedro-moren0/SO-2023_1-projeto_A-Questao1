#Lazy makefile
PROJ_NAME=mqp_scheduler
C_SOURCE=$(wildcard *.c)
OBJS=$(C_SOURCE: .c =.o)
CC=gcc
CC_FLAGS=-Wall

all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $@ $< $(CC_FLAGS)
