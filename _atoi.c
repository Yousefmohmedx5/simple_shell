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





