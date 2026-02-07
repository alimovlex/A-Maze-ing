/**
 * @file config.h
 * @brief Header for configuration file parsing.
 *
 * Defines the structure for storing configuration settings and the prototype
 * for the function that reads them from a file.
 */

#ifndef CONFIG_H
#define CONFIG_H

/**
 * @struct Config
 * @brief Holds the configuration settings for the maze.
 */
typedef struct {
    int width;
    int height;
    unsigned int seed;
} Config;

/**
 * @brief Parses a configuration file to load maze settings.
 *
 * @param filename The path to the configuration file.
 * @param config A pointer to the Config structure to populate.
 * @return 0 on success, -1 on failure.
 */
int parse_config(const char *filename, Config *config);

#endif // CONFIG_H
