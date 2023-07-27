#include "main.h"

/**
 * read_cmd - reads user input
 *
 * Return: returns the command back to the user
 */

char *read_cmd(void)
{
	char *buff = NULL; /* stores the address of the buffer */
	size_t n = 0; /* stores allocated size in bytes */
	ssize_t read_chars; /* holds the return value of getline function */

	while (1)
	{
		read_chars = getline(&buff, &n, stdin);

		if (read_chars == -1)
		{
			free(buff);
			exit(EXIT_SUCCESS); /* exits the shell */
		}
		else if (read_chars > 1 && buff[0] != '\n')
		{
			break; /* Break out of the loop for non-empty input */
		}

		if (buff[0] == '\n')
		{
			free(buff);
			buff = NULL;
			display_prompt();
			continue;
		}
	}

	return (buff);
}
