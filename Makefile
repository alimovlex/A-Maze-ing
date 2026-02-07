# A simple Makefile for the A-Maze-ing project

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRCS = main.c maze.c config.c utils.c
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
