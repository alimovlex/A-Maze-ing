
#include "maze.h"

//#define Log(fmt, ...) \
//    printf("[%s] [%s] [Line %d]: " fmt "\n", __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)

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

void fill_maze_parameters(char *buffer, t_maze *maze)
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

int read_file(const char *filename, t_maze *maze)
{
    const unsigned int  size = 74;
    char buffer[size];
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (-1);
    else
        read(fd, buffer, size - 1);
	fill_maze_parameters(buffer, maze);
	printf("Width: %d\nHeight: %d", maze->width, maze->height);
    init_grid(maze);
    rush(maze->exit_x, maze->exit_y);
    return 0;
}

t_maze *init_grid(t_maze *maze)
{
	int size = (maze->width * maze->height);
	printf("allocating %d bytes\n", size);
    t_cell *grid = (t_cell *)calloc(size, sizeof(t_cell));
    if (!grid)
        return NULL;
    int o = 0, x = 0, y = 0, z = 0;
    while (y < maze->height)
    {
        while (x < maze->width)
        {
            maze->grid[z]->y = y;
            maze->grid[z]->x = x;
            x++;
            z++;
        }
        x = 0;
        y++;
    }
    z = 0;
    // now the neighbor linking is in the making:
    while (maze->grid[z])
    {
        if (maze->grid[z - maze->width] != NULL) // checking for Nothern neighbor
            maze->grid[z]->options[o] = *maze->grid[z - maze->width];
        o++;
        if (maze->grid[z + 1] != NULL) // checking for Easter neighbor
            maze->grid[z]->options = maze->grid[z + 1];
        o++;
        if (maze->grid[z + maze->width] != NULL) // checking for Southern neighbor
            maze->grid[z]->options = maze->grid[z + maze->width];
        o++;
        if (maze->grid[z - 1] != NULL)
            maze->grid[z]->options = maze->grid[z - 1];
        o++;
        o = 0;
        z++;
    }
    return maze;
}

void free_maze(t_maze *maze)
{
    int z = 0;
    while (maze->grid[z])
    {
        t_cell *tmp = maze->grid[z];
        free(tmp);
        z++;
    }
    free(maze);
}
