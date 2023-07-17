#include "main.h"

/**
 * main - The main funcion
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: Returns 0
 */

int main(int argc, char **argv)
{
	char *cmd;
	/*Declaring cvoid variables*/
	(void)argc;
	(void)argv;

	if (isatty(STDIN_FILENO))
	{
		while (1) /*create an infinite loop*/
		{
			display_prompt();
			cmd = read_cmd();
			if (cmd == NULL)
			{
				break;
			}
			execute_cmd(cmd);
			free(cmd);
		}
	}
	else
	{
		/*Non interactive mode*/
		while ((cmd = read_cmd()) != NULL)
		{
			execute_cmd(cmd);
			free(cmd);
		}
	}

	return (0);
}
