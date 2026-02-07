/**
 * @file utils.c
 * @brief Utility functions for the A-Maze-ing project.
 *
 * This file will contain helper functions, such as the hexadecimal converter.
 */

#include "utils.h"
#include <stdio.h>

/**
 * @brief Saves the maze to a file in hexadecimal format.
 *
 * Each cell's wall data is converted to a single hex digit.
 * The bits represent walls: West (1), South (2), East (4), North (8).
 * @param maze The maze to save.
 * @param filename The name of the file to save to.
 * @return 0 on success, -1 on failure.
 */
int save_maze_hex(const Maze *maze, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening output file");
        return -1;
    }

    for (int i = 0; i < maze->height; i++) {
        for (int j = 0; j < maze->width; j++) {
            int hex_val = 0;
            const Cell *cell = &maze->grid[i][j];

            if (cell->west_wall)  hex_val |= 1; // Bit 0
            if (cell->south_wall) hex_val |= 2; // Bit 1
            if (cell->east_wall)  hex_val |= 4; // Bit 2
            if (cell->north_wall) hex_val |= 8; // Bit 3

            fprintf(file, "%X", hex_val);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Maze successfully saved to %s\n", filename);
    return 0;
}
