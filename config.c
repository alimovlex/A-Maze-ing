/**
 * @file config.c
 * @brief Configuration file parser.
 *
 * This file will contain functions to read and parse a configuration file
 * that specifies the maze dimensions and other settings.
 */

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUF_SIZE 1024

/**
 * @brief Parses a configuration file to load maze settings.
 *
 * @param filename The path to the configuration file.
 * @param config A pointer to the Config structure to populate.
 * @return 0 on success, -1 on failure.
 */
int parse_config(const char *filename, Config *config) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening config file");
        return -1;
    }

    char line[LINE_BUF_SIZE];
    char key[LINE_BUF_SIZE];
    int value;

    while (fgets(line, sizeof(line), file)) {
        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == '\n') {
            continue;
        }

        if (sscanf(line, "%s %d", key, &value) == 2) {
            if (strcmp(key, "width") == 0) {
                config->width = value;
            } else if (strcmp(key, "height") == 0) {
                config->height = value;
            } else if (strcmp(key, "seed") == 0) {
                config->seed = (unsigned int)value;
            }
        }
    }

    fclose(file);
    return 0;
}
