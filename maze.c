#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "maze.h"

#define Log(fmt, ...) \
    printf("[%s] [%s] [Line %d]: " fmt "\n", __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)

#define A "o"
#define B "-"
#define C "|"
#define D " "

void	first_last(int x)
{
	int	width;

	width = x;
	while (width != 0)
	{
		if (width == x)
			printf(A);
		else if (width == 1)
			printf(A);
		else
			printf(B);
		width--;
	}
	printf("\n");
}

void	middle(int x)
{
	int	width;

	width = x;
	while (width != 0)
	{
		if (width == 1)
			printf(C);
		else if (width == x)
			printf(C);
		else
			printf(D);
		width--;
	}
	printf("\n");
}

void	rush(int x, int y)
{
	int	height;

	height = y -2;
	if (x <= 0 || y <= 0)
		return ;
	first_last(x);
	while (height > 0)
	{
		middle(x);
		height--;
	}
	if (y > 1)
	{
		first_last(x);
	}
}

void fill_maze_parameters(char *buffer, struct s_maze *maze)
{
    const int size = 6;
    int values[size], i = 0;
    maze->is_perfect = false;
    while (*buffer && i < size)
    {
        if (isdigit(*buffer))
        {
            char *end;
            int value = (int)strtol(buffer, &end, 10);
            //printf("Assigned number: %d\n", value);
            *(values + i) = value;
            i++;
            buffer = end;
        }
        else if (strcmp(buffer, "True") == 0)
            maze->is_perfect = true;
        else
            buffer++;
    }
    maze->width = values[0];
    maze->height = values[1];
    maze->entry_x = values[2];
    maze->entry_y = values[3];
    maze->exit_x = values[4];
    maze->exit_y = values[5];
    printf("%d\n", maze->is_perfect);
    /*
    i = 0;
    while(i < size)
        printf("ASSIGNED VALUES = %d\n", values[i++]);
    */
}

int read_file(const char *filename)
{
    const unsigned int  size = 74;
    char buffer[size];
    struct s_maze maze;
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (-1);
    else
        read(fd, buffer, size - 1);
    //printf("%s", buffer);
    fill_maze_parameters(buffer, &maze);
    rush(maze.exit_x, maze.exit_y);
    return 0;
}
