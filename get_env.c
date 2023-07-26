#include "main.h"

/**
 * get_environment - displays the current environment variables
 */

void get_environment(void)
{
	int i = 0;
	char *env_var;

	while ((env_var = environ[i]) != NULL)
	{
		size_t len = strlen(env_var);

		write(STDOUT_FILENO, env_var, len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
