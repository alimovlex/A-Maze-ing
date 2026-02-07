/**
 * @file maze.c
 * @brief Implementation of maze generation and manipulation functions.
 *
 * This file will contain the logic for the Recursive Backtracker algorithm
 * to generate the maze, as well as functions to display it.
 */

#include "maze.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Allocates and initializes a new maze.
 *
 * @param width The width of the maze.
 * @param height The height of the maze.
 * @return A pointer to the newly created Maze, or NULL if memory allocation fails.
 */
Maze* create_maze(int width, int height) {
    // Allocate memory for the Maze structure itself
    Maze *maze = (Maze*)malloc(sizeof(Maze));
    if (!maze) {
        perror("Failed to allocate memory for maze");
        return NULL;
    }
    maze->width = width;
    maze->height = height;

    // Allocate memory for the rows of the grid (array of pointers to Cell)
    maze->grid = (Cell**)malloc(height * sizeof(Cell*));
    if (!maze->grid) {
        perror("Failed to allocate memory for maze grid rows");
        free(maze);
        return NULL;
    }

    // Allocate memory for each row and initialize cells
    for (int i = 0; i < height; i++) {
        maze->grid[i] = (Cell*)malloc(width * sizeof(Cell));
        if (!maze->grid[i]) {
            perror("Failed to allocate memory for maze grid column");
            // Free previously allocated rows
            for (int j = 0; j < i; j++) {
                free(maze->grid[j]);
            }
            free(maze->grid);
            free(maze);
            return NULL;
        }

        // Initialize each cell in the row
        for (int j = 0; j < width; j++) {
            maze->grid[i][j] = (Cell){
                .north_wall = true,
                .east_wall = true,
                .south_wall = true,
                .west_wall = true,
                .visited = false
            };
        }
    }

    return maze;
}

/**
 * @brief Frees the memory allocated for the maze.
 *
 * @param maze A pointer to the maze to be freed.
 */
#include <time.h>

// Helper structure for the generation stack
typedef struct {
    int x, y;
} Point;

// Helper function to remove walls between two adjacent cells
static void remove_wall(Cell *current, Cell *next, int dx, int dy) {
    if (dx == 1) { // Move East
        current->east_wall = false;
        next->west_wall = false;
    } else if (dx == -1) { // Move West
        current->west_wall = false;
        next->east_wall = false;
    } else if (dy == 1) { // Move South
        current->south_wall = false;
        next->north_wall = false;
    } else if (dy == -1) { // Move North
        current->north_wall = false;
        next->south_wall = false;
    }
}

/**
 * @brief Generates the maze using a Recursive Backtracker algorithm.
 *
 * @param maze The maze to generate.
 * @param start_x The starting X coordinate.
 * @param start_y The starting Y coordinate.
 */
void generate_maze(Maze *maze, int start_x, int start_y) {
    // Seed the random number generator
    srand(time(NULL));

    // Create a stack for backtracking
    Point *stack = (Point*)malloc(maze->width * maze->height * sizeof(Point));
    if (!stack) {
        perror("Failed to allocate memory for stack");
        return;
    }
    int stack_top = 0;

    // Start at the given coordinates
    int current_x = start_x;
    int current_y = start_y;
    maze->grid[current_y][current_x].visited = true;
    stack[stack_top++] = (Point){current_x, current_y};

    while (stack_top > 0) {
        // Get current cell from the top of the stack
        Point current_pos = stack[stack_top - 1];
        current_x = current_pos.x;
        current_y = current_pos.y;

        // Find unvisited neighbors
        Point neighbors[4];
        int neighbor_count = 0;

        // Directions: North, East, South, West
        int dx[] = {0, 1, 0, -1};
        int dy[] = {-1, 0, 1, 0};

        for (int i = 0; i < 4; i++) {
            int next_x = current_x + dx[i];
            int next_y = current_y + dy[i];

            // Check bounds and if visited
            if (next_x >= 0 && next_x < maze->width && next_y >= 0 && next_y < maze->height &&
                !maze->grid[next_y][next_x].visited) {
                neighbors[neighbor_count++] = (Point){next_x, next_y};
            }
        }

        if (neighbor_count > 0) {
            // Choose a random neighbor
            int rand_index = rand() % neighbor_count;
            Point next_pos = neighbors[rand_index];

            // Remove the wall between the current and next cell
            remove_wall(&maze->grid[current_y][current_x], &maze->grid[next_pos.y][next_pos.x],
                        next_pos.x - current_x, next_pos.y - current_y);

            // Move to the next cell
            maze->grid[next_pos.y][next_pos.x].visited = true;
            stack[stack_top++] = next_pos;
        } else {
            // Backtrack
            stack_top--;
        }
    }

    free(stack);
}

/**
 * @brief Displays the maze in the terminal using ASCII characters.
 *
 * @param maze The maze to display.
 */
void display_maze(const Maze *maze) {
    if (!maze) return;

    // Print the top wall of the maze
    for (int j = 0; j < maze->width; j++) {
        printf("+--");
    }
    printf("+\n");

    for (int i = 0; i < maze->height; i++) {
        // Print the west wall and cell content
        printf("|");
        for (int j = 0; j < maze->width; j++) {
            // A space for the path, then a wall if it exists
            printf("  %c", maze->grid[i][j].east_wall ? '|' : ' ');
        }
        printf("\n");

        // Print the south wall
        for (int j = 0; j < maze->width; j++) {
            printf("+%s", maze->grid[i][j].south_wall ? "--" : "  ");
        }
        printf("+\n");
    }
}

/**
 * @brief Carves a "42" pattern into the maze walls if it's large enough.
 *
 * @param maze The maze to modify.
 */
void carve_42_pattern(Maze *maze) {
    // Pattern dimensions (5x3 for each number, plus a 1-cell gap)
    const int pattern_width = 7;
    const int pattern_height = 5;

    // Check if the maze is large enough
    if (maze->width < pattern_width + 2 || maze->height < pattern_height + 2) {
        printf("Maze too small to carve '42' pattern.\n");
        return;
    }

    // Center the pattern
    int start_x = (maze->width - pattern_width) / 2;
    int start_y = (maze->height - pattern_height) / 2;

    // Define the '4' pattern (1 = wall, 0 = path)
    int pattern4[5][3] = {
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 1},
        {0, 0, 1},
        {0, 0, 1}
    };

    // Define the '2' pattern
    int pattern2[5][3] = {
        {1, 1, 1},
        {0, 0, 1},
        {1, 1, 1},
        {1, 0, 0},
        {1, 1, 1}
    };

    // Carve the '4'
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            if (pattern4[i][j] == 1) {
                Cell *cell = &maze->grid[start_y + i][start_x + j];
                cell->north_wall = cell->east_wall = cell->south_wall = cell->west_wall = true;
            }
        }
    }

    // Carve the '2'
    int start_2_x = start_x + 4; // Position '2' to the right of '4'
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            if (pattern2[i][j] == 1) {
                Cell *cell = &maze->grid[start_y + i][start_2_x + j];
                cell->north_wall = cell->east_wall = cell->south_wall = cell->west_wall = true;
            }
        }
    }
}

void free_maze(Maze *maze) {
    if (!maze) return;

    // Free each row in the grid
    for (int i = 0; i < maze->height; i++) {
        free(maze->grid[i]);
    }
    // Free the array of row pointers
    free(maze->grid);
    // Free the Maze structure itself
    free(maze);
}
