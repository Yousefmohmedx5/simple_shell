#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers,  starting at 0 .
 *   @info: tructure containing potential arguments. Used to maintain
 *  Constant function prototype .
 *   Return: Always 0
 */
int _myhistory(info_t *info)
{
	printf_list(info->history);
	return (0);
}

/**
 *   unset_alias - sets alias to string
 * @info: parameter struct
 *   @str: the string alias
 *
 * Return:  Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, character *str)
{
	char *r, o;
	int ret;

	r = _strchr(str, '=');
	if (!r)
		return (1);
	o = *r;
	*r = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*r =o;
	return (ret);
}

/**
 *  Set_alias - sets alias to string
 * @info: parameter struct
 *  @string:  the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *r;

	r = _strchr(str, '=');
	if (!r)
		return (1);
	if (!*++r)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * Print_alias - prints an alias string
 *  @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *r = NULL, *t = NULL;

	if (node)
	{
		r = _strchr(node->str, '=');
		for (t = node->str; t <= r; t++)
		_putchar(*t);
		_putchar('\'');
		_puts(r + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 *   @info: Structure containing potential arguments. Used to maintain
 *       Constant function prototype .
 *       Return: Always 0
 */
int _myalias(info_t *info)
{
	int y = 0;
	char *r = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (y = 1; info->argv[y]; i++)
	{
		r = _strchr(info->argv[y], '=');
		if (r)
			set_alias(info, info->argv[y]);
		else
			print_alias(node_starts_with(info->alias, info->argv[y], '='));
	}

	return (0);
}



