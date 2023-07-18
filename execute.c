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
		if (strcmp(argv[0], "exit") == 0)/*checks if the cmd is "exit"*/
		{
			if (argv[1] != NULL) /* checks if an argument is provided after 'exit' */
				exit(atoi(argv[1])); /*exits the shell with the inputed status*/
			for (i = 0; argv[i] != NULL; i++)
				free(argv[i]);
			free(argv);
			exit(0); /*exit the shell*/
		}
		else if (strcmp(argv[0], "env") == 0)/*checks if the cmd is "exit"*/
		{
			get_environment();
			for (i = 0; argv[i] != NULL; i++)
				free(argv[i]);
			free(argv);
			return;
		}
		child_id = fork();
		if (child_id == 0)
		{
			cmd = cmd_path(cmd);
			execve(cmd, argv, NULL);
			perror("Error");
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
			waitpid(child_id, &status, 0);
	}
	else
		fprintf(stderr, "Command not found: %s\n", cmd);

	for (i = 0; argv[i] != NULL; i++)
		free(argv[i]);
	free(argv);
}
