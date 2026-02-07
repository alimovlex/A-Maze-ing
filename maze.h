/**
 * @file maze.h
 * @brief Header file for maze generation and manipulation.
 *
 * This file defines the data structures and function prototypes for creating,
 * generating, and displaying the maze.
 */

#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>

/**
 * @struct Cell
 * @brief Represents a single cell in the maze.
 *
 * Each cell has four walls and a flag to indicate if it has been visited
 * during the generation process.
 */
typedef struct {
    bool north_wall;
    bool east_wall;
    bool south_wall;
    bool west_wall;
    bool visited;
} Cell;

/**
 * @struct Maze
 * @brief Represents the entire maze grid.
 *
 * Contains the dimensions of the maze and a 2D array of Cell structures.
 */
typedef struct {
    int width;
    int height;
    Cell **grid;
} Maze;

// Function prototypes for maze operations
Maze* create_maze(int width, int height);
void generate_maze(Maze *maze, int start_x, int start_y);
void display_maze(const Maze *maze);
void free_maze(Maze *maze);
void carve_42_pattern(Maze *maze);

#endif // MAZE_H
