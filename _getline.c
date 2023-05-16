#include "main.h"

/**
 * _read - read from a stream to a buffer
 *
 */

/**
 * _get_line - reads one line at a time from stdin and stores it in line.
 * @line: buffer containing the read line.
 * @len: size of buffer pointed by *line.
 * @stream: what file stream to read from
 *
 * Return: no of char read (Success) or -1 when EOF is reached or (Failure).
 */
int _get_line(char **line, size_t *len, FILE *fp)
{
	static char buffer[BUFFER_SIZE];
	static ssize_t b_idx, b_read;
	ssize_t t_b_read = 0;

	if (!line || !len || !fp)
		return (-1);
	if (!(*line) || !(*len))
	{
		*len = BUFFER_SIZE;
		if (!(*line = malloc(*len)))
			return (-1);
	}
	(*line)[0] = '\0';
	while (fgets(buffer, BUFFER_SIZE, fp))
	{
		if (*len - strlen(*line) < BUFFER_SIZE)
		{
			*len *= 2;
			if (!(*line = realloc(*line, *len)))
				return (-1);
		}
		strcat(*line, buffer);
		if ((*line)[strlen(*line) - 1] == '\n')
			return (strlen(*line));
	}
	return (-1);
}
