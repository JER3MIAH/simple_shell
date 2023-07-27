#include "main.h"

/**
 * trim_whitespace - Removes leading and trailing whitespace from a string.
 * @str: The input string to trim.
 *
 * Return: A pointer to the trimmed string.
 */

char *trim_whitespace(char *str)
{
	char *end;

	while (isspace((unsigned char)*str))
		str++;

	if (*str == '\0')
		return (str);

	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end))
		end--;

	*(end + 1) = '\0';

	return (str);
}
