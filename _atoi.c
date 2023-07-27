#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: if interactive mode 1 , 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @n: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char n, char *delim)
{
	while (*delim)
		if (*delim++ == n)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @m: The character to input
 * Return:  If m is alphabetic 1 , 0 otherwise
 */

int _isalpha(int m)
{
	if ((m >= 'a' && m <= 'z') || (m >= 'A' && m <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @f: the string to be converted
 * Return:  0 If no numbers in string, converted number otherwise
 */

int _atoi(char *f)
{
	int h, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (h = 0; f[h] != '\0' && flag != 2; h++)
	{
		if (f[h] == '-')
			sign *= -1;

		if (f[h] >= '0' && f[h] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (f[h] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}


==========================

builtin.c

#include "shell.h"

/**
 * _myexit - exits the shell
 * @info :  Structure containing potential arguments. Used to maintain
 * Constant function prototype.
 * Return : exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exit check;

	if (info->argv[1]) /* if there is an exit arguement */
	{
		exit check = _error atoi(info->argv[1]);
		if (exit check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->error_num = _erroratoi(info->argv[1]);
		return (-2);
	}
	info->error_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments . Used to maintain
 * Constant function prototype .
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *x, *dir, buffer[1024];
	int chdir_ret;

	x = getcwd(buffer, 1024);
	if (!x)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	If (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: ًWhat should this be ?  
*/
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(x);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: What should this be ? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the  process
 * @info: Structure containing potential arguments . Used to maintain
 * Constant  function prototype .
 * Return :  Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	If  (0)
		_puts(*arg_array); /* temp att_unused workaround 
*/
	return (0);
}
