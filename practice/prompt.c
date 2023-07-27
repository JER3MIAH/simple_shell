#include "main.h"

/**
 * display_prompt - displays a prompt for the user
 *
 */

void display_prompt(void)
{
	char *prompt = "(J^H)$ ";

	write(STDOUT_FILENO, prompt, strlen(prompt)); /*displays prompt*/
}
