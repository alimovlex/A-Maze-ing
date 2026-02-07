/**
 * @file utils.h
 * @brief Header for utility functions.
 *
 * Declares helper functions for the A-Maze-ing project, such as saving the maze
 * to a file in hexadecimal format.
 */

#ifndef UTILS_H
#define UTILS_H

#include "maze.h"

/**
 * @brief Saves the maze to a file in hexadecimal format.
 *
 * Each cell's wall data is converted to a single hex digit.
 * @param maze The maze to save.
 * @param filename The name of the file to save to.
 * @return 0 on success, -1 on failure.
 */
int save_maze_hex(const Maze *maze, const char *filename);

#endif // UTILS_H
