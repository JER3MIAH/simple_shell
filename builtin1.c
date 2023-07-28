#include "main.h"

/**
 * my_history - Displays a list of previously executed commands, one command per line,
 *              with line numbers starting from 0.
 * @info: Pointer to a structure that might contain additional arguments, ensuring a constant function prototype.
 *
 * Return: Always 0
 */
int my_history(info_t *info)
{
	/* Call 'print_list' to show the history list. */
	print_list(info->history);
	/* Return 0 to indicate successful execution. */
	return (0);
}

/**
 * unset_alias - Removes an alias.
 * @info: Pointer to the parameter struct.
 * @str: The string representing the alias to be removed in the format "alias_name".
 *
 * Return: Returns 0 on success, and 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	/* Find position of '=' in alias string. */
	p = _strchr(str, '=');
	if (!p)
	{
		/* If tere is no equal sign, return error (1). */
		return (1);
	}

	/* Store character after equal sign (alias value) in 'c'. */
	c = *p;
	/* Replace equal sign with null terminator 
		to separate alias name. */
	*p = 0;

	/* Get index of alias in alias list using 'get_node_index'. */
	ret = delete_node_at_index(&(info->alias),
							   get_node_index(info->alias, node_starts_with(info->alias, str, -1)));

	/* Restore equal sign character back to 
	 original position in 'str'. */
	*p = c;

	return (ret); /* Return 0 on success, 1 on error. */
}

/**
 * set_alias - Assigns an alias to a given string.
 * @info: Pointer to the parameter struct.
 * @str: String representing the alias in the format "alias_name=alias_value".
 *
 * Return: Returns 0 on success, and 1 on error.
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	/* Find position of the equal sign '=' in the alias string. */
	p = _strchr(str, '=');
	if (!p)
	{
		/* If there is no equal sign, return error (1). */
		return (1);
	}

	if (!*++p)
	{
		/* If there is no value after the equal sign, 
		unset the alias and return success (0). */
		return (unset_alias(info, str));
	}
		
	/* Unset any existing alias with the same name. */
	unset_alias(info, str);

	/* Add the new alias entry to the end of the alias list. */
	/* Return 0 on success, 1 on error. */
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Displays an alias string.
 * @node: Pointer to the alias node containing the alias string.
 *
 * Return: Returns 0 on success, and 1 on error.
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		/* Find position of equal sign in alias string. */
		p = _strchr(node->str, '=');
		/* Print alias name part up to equal sign. */
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\''); /* Print a single quote before alias value. */
		_puts(p + 1);	/* Print alias value part after equal sign. */
		/* Print a new line character to complete alias output. */
		_puts("'\n");
		return (0);		/* Return 0 on success. */
	}
	return (1); /* Return 1 on error (if node is NULL). */
}

/**
 * my_alias - Simulates the functionality of the alias built-in command (man alias).
 * @info: Pointer to a structure that may contain additional arguments,
 *        ensuring a constant function prototype.
 *
 * Return: Always 0
 */
int my_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	/* If the alias cmd is used without any arguments, print all aliases. */
	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node); /* Print each alias entry in the alias list. */
			node = node->next;
		}
		return (0);
	}

	/* Loop through each argument provided to the alias command. */
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
		{
			/* Set alias using provided argument. */
			set_alias(info, info->argv[i]);
		}
		else
		{
			/* Print alias by searching in the alias list. */
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
		}
	}

	return (0);
}
