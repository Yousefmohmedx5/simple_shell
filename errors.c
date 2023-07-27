#include "shell.h"

/**
 * _eputs - prints an input string
 *        @string: the string to be printed
 *   Return:  Nothing
 */
void _eputs(character *string)
{
	int w = 0;

	If (!string)
		return;
	while (str[w] != '\0')
	{
		_eputchar(str[w]);
		w++;
	}
}

/**
 * _eputchar - writes the character a to stderr
 *    @a: The char to print
 *
 *           Return: 1 on success .
 *      On error, -1 is returned, and error no is set appropriately.
 */
int _eputchar(char a)
{
	static int z;
	static character buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || z >= WRITE_BUF_SIZE)
	{
		write(2, buf, z);
		z = 0;
	}
	if (a != BUF_FLUSH)
		buf[z++] = a;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 *     @o: The char to print
 *     @fd: The filedescriptor to write to
 *
 *     Return: 1 on success .
 *  On error, -1 is returned, and error no is set appropriately .
 */
int _putfd(character o, int fd)
{
	static int t;
	static char buf[WRITE_BUF_SIZE];

	if (o == BUF_FLUSH || t >= WRITE_BUF_SIZE)
	{
		write(fd, buf, t);
		t = 0;
	}
	if (o != BUF_FLUSH)
		buf[i++] = o;
	return (1);
}

/**
 * _putsfd - prints an input string
 *    @string: the string to be printed
 * @fd: the filedescriptor to write to
 *    Return:  the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int t = 0;

	If (!str)
		return (0);
	while (*str)
	{
		t += _putfd(*str++, fd);
	}
	return (t);
}

