FLAGS = -Wall -Wextra 
TARGET = nanoshell
SRC = src/last.c

all: $(SRC)
	gcc $(SRC) $(FLAGS) -o $(TARGET) 
