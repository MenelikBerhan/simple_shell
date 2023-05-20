#include "main.h"

/**
 * _read - read from a stream to a buffer
 * @fp: input stream
 * @len: input string length
 * @line: line buffer
 *
 * Return: read string length and -1 if an error occurs
 */
int _read(FILE *fp, size_t *len, char **line)
{
	int c, i_mode = isatty(STDIN_FILENO);
	size_t line_len = strlen(*line);

	while (1)
	{
		c = fgetc(fp);
		if (line_len > *len - 1)
		{
			*len *= 2;
			*line = realloc(*line, *len);
			if (!(*line))
				return (-1);
		}
		if (c == '\n' && i_mode)
		{
			(*line)[line_len] = '\0';
			return (line_len);
		}
		if ((c == 4 || c == EOF) && line_len > 1)
		{
			if (i_mode)
			{
				c = 7;
				ungetc(c, fp);
				continue;
			}
			else
			{
				(*line)[line_len] = '\0';
				return (line_len);
			}
		}
		(*line)[line_len++] = (char)c;
	}
	return (-1);
}

/**
 * _get_line - reads one line at a time from stdin and stores it in line.
 * @line: buffer containing the read line.
 * @fp: what file stream to read from
 *
 * Return: no of char read (Success) or -1 when EOF is reached or (Failure).
 */
int _get_line(char **line, FILE *fp)
{
	size_t len = BUFFER_SIZE;
	int r_bytes;

	if (!line || !len || !fp)
		return (-1);
	*line = malloc(len);
	memset(*line, 0, len);
	if (!(*line))
		return (-1);
	memset(*line, 0, len);
	r_bytes = _read(fp, &len, line);
	return (r_bytes);
}
