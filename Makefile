# A simple Makefile for the A-Maze-ing project

CC = cc
CFLAGS = -g

SRCS = main.c maze.c maze_utils.c search.c 
OBJS = $(SRCS:.c=.o)

TARGET = amazing

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
