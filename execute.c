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
		else if (strcmp(argv[0], "cd") == 0)
		{
			/* Execute the cd command with the argument provided (argv[1]) */
			execute_cd(argv[1]);
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

/**
 * execute_cd - changes the current directory of the process
 * @dir: the directory to change to
 */
void execute_cd(char *dir)
{
	char *prev_dir;
	char *new_dir;

	prev_dir = getcwd(NULL, 0); /* Get the current working directory */

	if (dir == NULL || strcmp(dir, "~") == 0)
	{
		/* If no directory is given or "~" is provided, go to home directory */
		new_dir = getenv("HOME");
	}
	else if (strcmp(dir, "-") == 0)
	{
		/* If "-" is given, go to the previous directory */
		new_dir = getenv("OLDPWD");
	}
	else
	{
		new_dir = dir;
	}
	if (chdir(new_dir) == -1)
	{
		perror("cd");
		free(prev_dir); /* Free the memory used for the previous directory */
		return;
	}
	else
	{
		/* Update the PWD and OLDPWD environment variables */
		if (setenv("OLDPWD", prev_dir, 1) == -1)
		{
			perror("setenv");
			free(prev_dir);
			return;
		}
		if (setenv("PWD", new_dir, 1) == -1)
		{
			perror("setenv");
			free(prev_dir);
			return;
		}
	}

	free(prev_dir); /* Free the memory used for the previous directory */
}
