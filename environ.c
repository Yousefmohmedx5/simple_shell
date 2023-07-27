#include "shell.h"

/**
 * _myenv - prints the current environment
 *     @info: Structure containing potential arguments. Used to maintain
 *               Constant function prototype .
 *           Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info:       structure containing potential arguments. Used to maintain
 * @name:     env var name
 * Return: the value
 */
char *_getenv(info_t *info, constant character *name)
{
	list_t *node = info->env;
	char *v;

	while (node)
	{
		v = starts_with(node->str, name);
		if (v && *v)
			return (v);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *       Or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *                Constant function prototype.
 *     Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 *    @info: structure containing potential arguments. Used to maintain
 *                      Constant function prototype.
 *     Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int b;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (b = 1; b <= info->argc; b++)
		_unsetenv(info, info->argv[b]);

	return (0);
}

/**
 *         populate_env_list - populates env linked list
 *    @info: Structure containing potential arguments. Used to maintain
 *                       Constant function prototype.
 *    Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t b;

	for (b = 0; environ[b]; b++)
		add_node_end(&node, environ[b], 0);
	info->env = node;
	return (0);
}
