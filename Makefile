# Makefile
#
# Histórico
#
# - 11/10/2013: versão inicial
# - 13/11/2013: correção das regras

.PHONY=all

SRC:=edo.c util.c rkf45.c

INC:= metodos.h util.h

CC:=gcc
CFLAGS:=-W -Wall -pedantic -O3 -std=c11
LFLAGS:=-lm
BIN:=edo

all: $(SRC) $(INC)
	$(CC) $(CFLAGS) $(SRC) $(LFLAGS) -o $(BIN)
