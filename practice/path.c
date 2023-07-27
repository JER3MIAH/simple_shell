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
			return (cmd);
		return (NULL);
	}
	return (NULL);
}

/**
 * concat_paths - Concatenate two strings
 * @path1: the first path
 * @path2: the second path
 *
 * Return: A pointer to the new concatenated string, or NULL on failure
 */
char *concat_paths(const char *path1, const char *path2)
{
	size_t len1 = strlen(path1);
	size_t len2 = strlen(path2);
	char *result = malloc(len1 + len2 + 1);

	if (result == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	strcpy(result, path1);
	strcat(result, path2);
	return (result);
}
