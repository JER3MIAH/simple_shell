#include "main.h"

/**
 * tokenize_cmd - splits up entered string into an array of strings
 * @cmd: the command string to be tokenized
 *
 * Return: An array of tokens
 */

char **tokenize_cmd(char *cmd)
{
	char **buff_copy = NULL; /*holds a copy of or string(buff)*/
	char *delim = " \n";
	char *token;
	int i = 0;
	int j;
	int size = 1;

	buff_copy = malloc(size * sizeof(char *));

	if (buff_copy == NULL)
	{
		perror("memory allocation failed");
		exit(EXIT_FAILURE);
	}

	token = strtok(cmd, delim);

	while (token)
	{
		buff_copy[i] = strdup(token);
		i++;
		size++;
		buff_copy = realloc(buff_copy, size * sizeof(char *));

		if (buff_copy == NULL)
		{
			perror("memory allocation failed");
			for (j = 0; j < i; j++)
			{
				free(buff_copy[j]);
			}
			free(buff_copy);
			free(token);
			exit(EXIT_FAILURE);
		}
		token = strtok(NULL, delim);
	}
	buff_copy[i] = NULL;
	return (buff_copy);
}
