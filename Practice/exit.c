#include "main.h"

/**
 * _strncpy - Copies a string up to a specified length.
 * @dest: Pointer to the destination string where the content will be copied.
 * @src: Pointer to the source string from which content will be copied.
 * @n: The number of characters to be copied from the source string.
 *
 * Return: Returns a pointer to the destination string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	/* Copy characters from source to destination up to n characters */
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}

	/* Fill the remaining characters in destination with null bytes ('\0') */
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}

	return (s);
}

/**
 * _strncat - Concatenates two strings up to a specified length.
 * @dest: Pointer to the first string (destination).
 * @src: Pointer to the second string (source).
 * @n: The maximum number of bytes to be used from the source string.
 *
 * Return: Returns a pointer to the concatenated string (dest).
 */
char *_strncat(char *dest, char *src, int n)
{
	int i;
	int j;
	char *s = dest;

	/* Find the end of the destination string */
	i = 0;
	while (dest[i] != '\0')
		i++;

	/* Append characters from src to dest up to n characters */
	j = 0;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	/* Null-terminate the concatenated string */
	if (j < n)
		dest[i] = '\0';

	return (s);
}

/**
 * _strchr - Locates a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 *
 * Return: A pointer to the memory area of 's' where 'c' is found,
 *         or NULL if 'c' is not present in 's'.
 */
char *_strchr(char *s, char c)
{
	/* Iterate through the string until the character 'c' is found */
	do
	{
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	/* Return NULL if 'c' is not present in 's' */
	return (NULL);
}
