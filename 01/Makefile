# Minimal Makefile to compile main.c into a binary

CC      ?= cc
CFLAGS  ?= -Wall -Wextra -O2 -std=c11

SRC     := main.c
BIN     := main

.PHONY: all clean run

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)

run: $(BIN)
	./$(BIN) < input.txt

clean:
	rm -f $(BIN)
