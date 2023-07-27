#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return:  if interactive mode 1 , 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @x: The char to check
 * @delim: the delimeter string
 * Return:  If true 1 ,  If false 0
 */
int is_delim(char x, char *delim)
{
	while (*delim)
		if (*delim++ == x)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@x: The char to input
 *Return: If x is alphabetic 1 ,  Otherwise 0
 */

int _isalpha(int x)
{
	if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@r: The string to be converted
 *Return:  If no numbers in string 0 , converted number otherwise
 */

int _atoi(char *r)
{
	int y, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (y = 0;  r[y] != '\0' && flag != 2; y++)
	{
		if (r[y] == '-')
			sign *= -1;

		if (r[y] >= '0' && r[y] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (r[y] - '0');
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

