#include "main.h"

/**
 * execute_cmd - executes the command provided by the user
 * @cmd: the command to be executed
 *
 */

void execute_cmd(char *cmd)
{
	pid_t child_id;
	int status; /*stores the exit status of child process*/
	char **argv;
	int i;

	argv = tokenize_cmd(cmd); /*tokenizes the command*/

	if (argv)
	{
		child_id = fork();
		if (child_id == 0)
		{
			execve(cmd, argv, NULL);
			perror("execution failed");
			free(argv);
			exit(EXIT_FAILURE);
		}
		else if (child_id == -1)
		{
			perror("Fork failed");
			free(argv);
			exit(EXIT_FAILURE);
		}
		else /*parent process*/
		{
			waitpid(child_id, &status, 0);
		}
	}
	else
	{
		fprintf(stderr, "Command not found: %s\n", cmd);
	}

	for (i = 0; argv[i] != NULL; i++)
	{
		free(argv[i]);
	}
	free(argv);
}
