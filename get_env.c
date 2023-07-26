#include "main.h"

/**
 * get_environment - displays the current environment variables
 */

void get_environment(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
