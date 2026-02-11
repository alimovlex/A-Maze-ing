#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#pragma once

typedef struct s_keyvaluepair
{
    char *key;
    void *value;
} t_keyvaluepair;

typedef struct s_cell;

typedef struct s_maze
{
    int width, height;
    int entry_x, entry_y, exit_x, exit_y;
    char *output_filename;
    bool is_perfect;
    struct s_cell **grid;
} t_maze;

typedef struct s_cell
{
    int x, y;
    struct s_maze maze;
    struct s_cell **options; // between 0 and 4.
    struct s_cell **walled; // between 0 and 4.
} t_cell;

void rush(int x, int y);
int read_file(const char *filename, t_maze *maze);
void init_grid(t_maze *maze);
void free_maze(t_maze *maze);
void fill_maze_parameters(char *buffer, t_maze *maze);
