#include "shell.h"
#include <stddef.h>
/**
 * input_buf - buffers chained commands
 * @info:  Parameter struct
 * @buf: Address of buffer
 * @len:   Address of len var
 *
 * Return: bytes read
 */
size_t input_buf(info_t *info, char **buf, size_t *len)
{
	size_t x = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*free((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE GETLINE
		x = getline(buf, &len_p, stdin);
#else
		x = _getline(info, buf, &len_p);
#endif
		if (x > 0)
		{
			if ((*buf)[x - 1] == '\n')
			{
				(*buf)[x - 1] = '\0'; /* remove trailing newline */
				x--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (strchr(*buf, ';')) is this a command chain? */
			{
				*len = x;
				info->cmd_buf = buf;
			}
		}
	}
	return (x);
}

/**
 * get_input - gets a line minus the newline
 * @info:   Parameter struct
 * Return:Bytes read
 */
size_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t h, g, len;
	size_t x = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (x == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		g = h; /* init new iterator to current buf position */
		p = buf + h; /* get pointer for return */

		check_chain(info, buf, &g, h, len);
		while (g < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &g))
				break;
			g++;
		}

		h = g + 1; /* increment past nulled ';'' */
		if (h >= len) /* reached end of buffer? */
		{
			h = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info:  Parameter struct
 * @buf: buffer
 * @c: size
 *
 * Return: u
 */
size_t read_buf(info_t *info, char *buf, size_t *c)
{
	size_t u = 0;

	if (*c)
		return (0);
	u = read(info->readfd, buf, READ_BUF_SIZE);
	if (u >= 0)
		*c = u;
	return (u);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: Parameter struct
 * @ptr: Address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: o
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t l, len;
	size_t k;
	size_t r = 0, o = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		o = *length;
	if (l == len)
		l = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + l, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, o, o ? o + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (o)
		_strncat(new_p, buf + l, k - l);
	else
		_strncpy(new_p, buf + l, k - l + 1);

	o += k - l;
	l = k;
	p = new_p;

	if (length)
		*length = o;
	*ptr = p;
	return (o);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

