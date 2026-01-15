CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
TARGET = nanoshell

all: $(TARGET)

$(TARGET): src/main.c src/parser.c src/builtins.c include/nanoshell.h
	$(CC) $(CFLAGS) -o $(TARGET) src/main.c src/parser.c src/builtins.c

clean:
	rm -f $(TARGET)

re: clean all

.PHONY: all clean re