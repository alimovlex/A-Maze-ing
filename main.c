
#include "maze.h"
//#define Log(fmt, ...) \
//    printf("[%s] [%s] [Line %d]: " fmt "\n", __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)

int	main(int argc, char **argv)
{
    const char *filename = "config.txt";
    char argument[strlen(filename) + 1];
    const char *src = *(++argv);
	t_maze *maze = malloc(1 * sizeof(t_maze));
	if (!maze)
		return 1;
    int i = 0;
    if (argc > 1 && argc < 3)
        while(*src && i < strlen(filename))
            argument[i++] = *src++;
    argument[i] = '\0';
    if (strcmp(filename, argument) == 0)
        read_file(filename, maze);
    else
        printf("Test error\n");//Log("No match: %s != %s", filename, argument);

	free_maze(maze);
	return (0);
}
