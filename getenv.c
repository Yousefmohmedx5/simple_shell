#include "shell.h"

/**
 *   get_environ - returns the string array copy of our environ
 * @info:     structure containing potential arguments. Used to maintain
 *      Constant function prototype.
 *  Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv -   remove an environment variable
 * @info: structure containing potential arguments. Used to maintain
 *           Constant function prototype .
 *  Return: On delete 1  , 0 otherwise
 * @var: the String env var property
 */
int _unsetenv(info_t *info, character *var)
{
	list_t *node = info->env;
	size_t x = 0;
	char *c;

	if (!node || !var)
		return (0);

	while (node)
	{
		c = starts_with(node->str, var);
		if (c && *c == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), x);
			x = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		x++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *        Or modify an existing one
 * @info:    Structure containing potential arguments. Used to maintain
 *    Constant function prototype .
 * @var: the string env var property
 * @value:    The string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, character *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *c;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		c = starts_with(node->str, var);
		if (c && *c == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}








