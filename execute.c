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
		if (execute_builtin_cmd(argv[0]))
		{
			for (i = 0; argv[i] != NULL; i++)
				free(argv[i]);
			free(argv);
			return (EXIT_SUCCESS);
		}
		else
			execute_external_cmd(argv, cmd);
	}
	else
	{
		write(STDERR_FILENO, "Command not found\n", 18);
		return (EXIT_FAILURE);
	}
	for (i = 0; argv[i] != NULL; i++)
		free(argv[i]);
	free(argv);
	return (EXIT_SUCCESS);
}

/**
 * execute_external_cmd - executes the external command provided by the user
 * @argv: argument vector. array of strings
 * @buff: command taken
 */
void execute_external_cmd(char **argv, char *buff)
{
	pid_t child_id;
	int status; /*stores the exit status of child process*/

	child_id = fork();
	if (child_id == 0)
	{
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
			free_argv(argv);
			free(buff);
			exit(EXIT_FAILURE);
		}
		execve(cmd_path_result, argv, NULL);
		perror("Error");
		free(cmd_path_result);
		free(buff);
		free_argv(argv);
		exit(EXIT_FAILURE);
	}
	else if (child_id == -1)
	{
		perror("Fork failed");
		free(buff);
		free_argv(argv);
		exit(EXIT_FAILURE);
	}
	else /*parent process*/
		waitpid(child_id, &status, 0);
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
 * @cmd: command
 *
 * Return: 1 if the command is a built-in command, 0 otherwise
 */
int execute_builtin_cmd(char *cmd)
{
	if (strcmp(cmd, "exit") == 0)
	{
		return (1); /* exit the shell */
	}
	else if (strcmp(cmd, "env") == 0)
	{
		get_environment();
		return (0);
	}

	return (0);
}
