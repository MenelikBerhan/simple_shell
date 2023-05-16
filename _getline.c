# include "main.h"

/**
 * _get_line - reads one line at a time from stdin and stores it in line.
 * @line: a pointer to store the address of the buffer containing the read line.
 * @len: size of buffer pointed by *line.
 *
 * Return: number of characters read (Success) or -1 when EOF is reached or (Failure).
*/
int _get_line(char **line, size_t *len) /* add - how to only read up to new line and fix std_in position after new line for next read */
{
	/* bug to fix 
	 1. - when reading from cat file(with multiple lines) all lines read as one. Should read one line at a time.
	 possible solution:
	 read one char at a time
	 stop when new line reached

	 2. for getline when reading a line if ^D is typed once and no chars bfr it it stops reading (works for us)
		but when there is atleast one char befroe ^D getline still waits and it will quit if the nxt char is ^D
		but continues to read is another char is typed after ^D
	 */
	ssize_t nread;

	/* to add management of *line size here (like getline)
	If  *lineptr  is  set to NULL and *n is set 0 before the
       call, then getline() will allocate a buffer for  storing
       the  line.  This buffer should be freed by the user pro‐
       gram even if getline() failed.

       Alternatively, before calling  getline(),  *lineptr  can
       contain  a  pointer  to  a malloc(3)-allocated buffer *n
       bytes in size.  If the buffer is  not  large  enough  to
       hold the line, getline() resizes it with realloc(3), up‐
       dating *lineptr and *n as necessary.

	check if nread ==  (*len) - 1 and if so realloc here and read remaining
	if (*len == 0 && *line == NULL)
	{
		*len = 20;
		*line = malloc(sizeof(char) * (*len));
	}
	memset(line, 0, *len); */

	/* read returns 0 when end of file is reached */
	nread = read(STDIN_FILENO, *line, (*len) - 1);

	/* printf("in get line line[%ld] = %c", nread, (*line)[nread]); */
	(*line)[(int)nread] = 0;
	if (nread == 0)
		return (-1);	

	return (nread);
}
