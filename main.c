#include "main.h"

/**
 * main - check the code
 * @agv: The argument vector
 * @agc: The argument count.
 * @env: The environment variable
 *
 * Return: 0.
 */
int main(int agc, char **agv, char **envp)
{
	if (agc == 1)
		prompt(agv, envp);
	return (0);
}
