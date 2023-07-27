#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info:   parameter struct
 * @buf: Address of buffer
 * @len:    Address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t n = 0;
	size_t len_p = 0;

	if (!*len) /* If nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		n = getline(buf, &len_p, stdin);
#else
		n = _getline(info, buf, &len_p);
#endif
		if (n > 0)
		{
			if ((*buf)[n - 1] == '\n')
			{
				(*buf)[n - 1] = '\0'; /* remove trailing newline */
				n--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = n;
				info->cmd_buf = buf;
			}
		}
	}
	return (n);
}

/**
 *   get_input - gets a line minus the newline
 *  @info:    parameter struct
 *
 * Return:   bytes read
 */
ssize_t get_input(info_t *info)
{
	static character *buf; /* the ';' command chain buffer */
	static size_t u, o, len;
	ssize_t n = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	n = input_buf(info, &buf, &len);
	if (n == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		o = u; /* init new iterator to current buf position */
		p = buf + u; /* get pointer for return */

		check_chain(info, buf, &o, u, len);
		while (o < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &o))
				break;
			o++;
		}

		u = o + 1; /* increment past nulled ';'' */
		if (u >= len) /* reached end of buffer? */
		{
			u = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (n); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info:   parameter struct
 * @buf:  buffer
 * @x:      size
 *
 * Return: b
 */
ssize_t read_buf(info_t *info, char *buf, size_t *x)
{
	ssize_t b = 0;

	if (*x)
		return (0);
	b = read(info->readfd, buf, READ_BUF_SIZE);
	if (b >= 0)
		*x = b;
	return (b);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info:     parameter struct
 * @ptr:  Address of pointer to buffer, preallocated or NULL
 * @length:   size of preallocated ptr buffer if not NULL
 *
 * Return: f
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, f, f ? f + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (f)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	f += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = f;
	*ptr = p;
	return (f);
}

/**
 *       SigintHandler - blocks ctrl-C
 *  @sig_num: the signal number
 *   Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}



