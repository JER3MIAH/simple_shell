#include "main.h"

/**
 * main - The main funcion
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: Returns the exit status
 */

int main(int argc, char **argv)
{
	struct sigaction sa;
	/*Declaring cvoid variables*/
	(void)argc;
	(void)argv;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	if (isatty(STDIN_FILENO))
	{
		interactive_mode();
	}
	else
	{
		non_interactive_mode();
	}

	return (0);
}

/**
 * interactive_mode - Run the shell in interactive mode.
 *
 */
void interactive_mode(void)
{
	char *cmd;

	while (1) /*create an infinite loop*/
	{
		display_prompt();
		cmd = read_cmd();
		if (cmd == NULL)
		{
			free(cmd);
			continue;
		}
		trim_whitespace(cmd);
		if (strcmp(cmd, "exit") == 0) /* check for "exit" command */
		{
			free(cmd);
			break; /* break out of the loop to terminate the shell */
		}
		execute_cmd(cmd);
		free(cmd);
	}
}

/**
 * non_interactive_mode - Run the shell in non-interactive mode.
 *
 */
void non_interactive_mode(void)
{
	char *cmd;

	while ((cmd = read_cmd()) != NULL)
	{
		execute_cmd(cmd);
		free(cmd);
	}
}

/**
 * sigint_handler - Signal handler for SIGINT (Ctrl+C).
 * @sig: The signal number.
 */
void sigint_handler(int sig)
{
	/*Display a new line to move the prompt to a new line after Ctrl+C*/
	write(STDOUT_FILENO, "\n", 1);

	/*Perform any necessary cleanup here if needed (e.g., free allocated memory)*/

	/* Re-display the prompt to allow the user to continue entering commands*/
	display_prompt();

	(void)sig;
}
