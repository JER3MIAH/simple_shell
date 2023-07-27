#include "main.h"

/**
 * execute_cmd - executes the command provided by the user
 * @cmd: the command to be executed
 * Return: exit success
 */

int execute_cmd(char *cmd)
{
	char **argv;
	int i;

	cmd = trim_whitespace(cmd);

	if (strlen(cmd) == 0)
	{
		return (EXIT_SUCCESS);
	}

	argv = tokenize_cmd(cmd); /* Tokenizes the command */
	if (argv && argv[0])
	{
		if (execute_builtin_cmd(argv))
		{
			for (i = 0; argv[i] != NULL; i++)
				free(argv[i]);
			free(argv);
			return (EXIT_SUCCESS);
		}
		execute_external_cmd(argv);
	}
	else
	{
		write(STDERR_FILENO, "Command not found\n", 18);
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}

/**
 * execute_external_cmd - executes the external command provided by the user
 * @argv: argument vector. array of strings
 *
 */
void execute_external_cmd(char **argv)
{
	int status; /* stores the exit status of child process */
	pid_t child_id;

	char *cmd_path_result = cmd_path(argv[0]);

	if (cmd_path_result == NULL)
	{
		/* Print the error message in the specified format */
		char *program_name = argv[0];
		char *error_msg = concat_paths("./hsh: ", "1: ");
		char not_found_msg[] = ": not found\n";

		write(STDERR_FILENO, error_msg, strlen(error_msg));
		write(STDERR_FILENO, program_name, strlen(program_name));
		write(STDERR_FILENO, not_found_msg, sizeof(not_found_msg) - 1);
		free(error_msg);
		return;
	}
	child_id = fork();
	if (child_id == 0)
	{
		execve(cmd_path_result, argv, NULL);
		perror("Error");
		free(cmd_path_result);
		free_argv(argv);
		exit(EXIT_FAILURE);
	}
	else if (child_id == -1)
	{
		perror("Fork failed");
		free(cmd_path_result);
		free_argv(argv);
		exit(EXIT_FAILURE);
	}
	else /* parent process */
	{
		waitpid(child_id, &status, 0);
		free(cmd_path_result);
	}

}

/**
 * free_argv - frees the memory allocated for the argument vector
 * @argv: argument vector. array of strings
 *
 */
void free_argv(char **argv)
{
	int i;

	for (i = 0; argv[i] != NULL; i++)
		free(argv[i]);
	free(argv);
}


/**
 * execute_builtin_cmd - executes the built-in command provided by the user
 * @argv: argument vector. array of strings
 *
 * Return: 1 if the command is a built-in command, 0 otherwise
 */
int execute_builtin_cmd(char **argv)
{
	if (strcmp(argv[0], "exit") == 0)
	{
		if (argv[1] != NULL) /* checks if an argument is provided after 'exit' */
			exit(atoi(argv[1])); /* exits the shell with the input status */
		exit(0); /* exit the shell */
	}
	else if (strcmp(argv[0], "env") == 0)
	{
		get_environment();
		return (1);
	}
	else if (strcmp(argv[0], "cd") == 0)
	{
		/* Execute the cd command with the argument provided (argv[1]) */
		execute_cd(argv[1]);
		return (1);
	}

	return (0);
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
		new_dir = dir;
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
