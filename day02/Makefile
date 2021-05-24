.PHONY: clean main all

CC=gcc
SRCS=$(wildcard *.c)
BASEDIR=$(shell pwd)
OBJDIR:=$(BASEDIR)/obj
$(shell mkdir -p $(OBJDIR))

OBJS=$(SRCS:.c=.o)

OBJS:=$(addprefix $(OBJDIR)/, $(OBJS))

BIN:=main

all : $(BIN)

main : $(OBJS)
	# @echo $(SRCS)
	# @echo $(OBJS)
	$(CC) -o $@ $^

%.o : %.c
	$(CC) -c $< -o $@

clean :
	rm -rf $(OBJS)

rebuild : clean main
