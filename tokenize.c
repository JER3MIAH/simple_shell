#include "main.h"

/**
 * tokenize_cmd - Tokenizes the input command string into an array of strings.
 * @cmd: The command string to be tokenized.
 *
 * Return: An array of tokens.
 */
char **tokenize_cmd(char *cmd)
{
	char *cmd_copy = strdup(cmd);
	char **buff_copy;

	if (cmd_copy == NULL)
	{
		perror("memory allocation failed");
		exit(EXIT_FAILURE);
	}

	buff_copy = tokenize_helper(cmd_copy);

	return (buff_copy);
}

/**
 * tokenize_helper - Helper function for tokenizing the command.
 * @cmd_copy: The copy of the command string to be tokenized.
 *
 * Return: An array of tokens.
 */
char **tokenize_helper(char *cmd_copy)
{
	char **buff_copy = NULL;
	char *delim = " \n";
	char *token;
	int i = 0;
	int j;
	int size = 1;

	buff_copy = malloc(size * sizeof(char *));
	if (buff_copy == NULL)
	{
		perror("memory allocation failed");
		free(cmd_copy); /* Free the copied command in case of failure */
		exit(EXIT_FAILURE);
	}

	token = strtok(cmd_copy, delim);
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
				free(buff_copy[j]);
			free(buff_copy);
			free(cmd_copy); /* Free the copied command in case of failure */
			exit(EXIT_FAILURE);
		}
		token = strtok(NULL, delim);
	}
	buff_copy[i] = NULL;

	return (buff_copy);
}
