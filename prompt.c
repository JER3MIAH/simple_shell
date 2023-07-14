#include "main.h"

/**
 * prompt - The function that display prompt and wait for the user to
 * type a command.
 * @agv: The argument vector
 * @envp: The environment variable
 *
 * Return: The prompt.
 */
void prompt(char **agv, char **envp)
{
	ssize_t num_core;
	int x, stat = 0;
	size_t n = 0;
	char *skills = NULL;

	char *argv[] = {NULL, NULL};

	pid_t child_id;

	while (1)
	{
		printf("Cisfun$ ");

		num_core = getline(&skills, &n, stdin);
		if (num_core == -1)
		{
			free(skills);
			exit(EXIT_FAILURE);
		}
		x = 0;
		while (skills[x])
		{
			if (skills[x] == '\n')
				skills[x] = 0;
			x++;
		}
		argv[0] = skills;
		child_id = fork();
		if (child_id == -1)
		{
			free(skills);
			exit(EXIT_FAILURE);
		}
		if (child_id == 0)
		{
			if (execve(argv[0], argv, envp) == -1)
				printf("%s: No such file or directory\n", agv[0]);
		}
		else
			wait(&stat);
	}
}
