<<<<<<< HEAD
=======
#include <stdbool.h>
#pragma once
struct s_maze
{
    int width, height;
    int entry_x, entry_y, exit_x, exit_y;
    char *output_filename;
    bool is_perfect;
};

void rush(int x, int y);
int read_file(const char *filename);
>>>>>>> origin/alalimov-test
