#include "main.h"

/**
 * read_cmd - reads user input
 *
 * Return: returns the command back to the user
 */

char *read_cmd(void)
{
	char *buff; /*stores the address of the buffer*/
	size_t n = 0; /*stores alocated size in bytes*/
	ssize_t read_chars; /*holds the return value of getline function*/

	read_chars = getline(&buff, &n, stdin);

	if (read_chars == -1)
	{
		printf("Exiting the shell...\n");
		return (NULL);
		free(buff);
	}
	else if (read_chars == 0)
	{
		return (buff);
		free(buff);
	}

	printf("%s\n", buff);

	return (buff);
}
