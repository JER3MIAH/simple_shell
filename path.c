#include "main.h"

/**
 * cmd_path - finds the path for a command
 * @cmd: the command
 * Return: the path to the command if its found, NULL otherwise
 */

char *cmd_path(char *cmd)
{
	char *path;
	char *path_copy;
	char *path_token;
	char *file_path;
	int cmd_lenght;
	int dir_length;
	struct stat buff;

	path = getenv("PATH");
	
	if (path != NULL)
	{
		path_copy = strdup(path);
		cmd_lenght = strlen(cmd);
		path_token = strtok(path_copy, ":");

		while (path_token != NULL)
		{
			dir_length = strlen(path_token);
			file_path = malloc(cmd_lenght + dir_length + 2);
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, cmd);
			strcat(file_path, "\0");

			if (stat(file_path, &buff) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);

		if (stat(cmd, &buff) == 0)
		{
			return (cmd);
		}

		return(NULL);
	}
	return (NULL);
}
