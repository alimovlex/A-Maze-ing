/**
 * @file main.c
 * @brief Main entry point for the A-Maze-ing project.
 *
 * This file contains the main function that drives the maze generation and display.
 * It will handle command-line arguments, read the configuration, generate the maze,
 * and then display it in the terminal.
 */

#include <stdio.h>
#include <stdlib.h> // For srand
#include "maze.h"
#include "config.h"
#include "utils.h"

/**
 * @brief The main function.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return 0 on success, non-zero on failure.
 */
int main(int argc, char *argv[]) {
        Config config;
    if (parse_config("config.txt", &config) != 0) {
        fprintf(stderr, "Error reading config file.\n");
        return 1;
    }

    // Seed the random number generator for reproducibility
    srand(config.seed);

    // Create the maze using dimensions from config
    Maze *maze = create_maze(config.width, config.height);
    if (!maze) {
        fprintf(stderr, "Error creating maze.\n");
        return 1;
    }

    // Generate the maze starting from the top-left corner (0, 0)
    generate_maze(maze, 0, 0);

    // Carve the "42" pattern into the maze
    carve_42_pattern(maze);

    // Display the generated maze
    printf("Generated Maze:\n");
    display_maze(maze);

        // Save the maze to a file
    if (save_maze_hex(maze, "maze.txt") != 0) {
        fprintf(stderr, "Error saving maze to file.\n");
        // The program can still exit gracefully even if saving fails
    }

    // Clean up allocated memory
    free_maze(maze);

    return 0;
}
