#include "main.h"

/**
 * count_tokens - count no of elements in an array
 * @arr: array under review
 *
 * Return: no of tokens
 */
int count_tokens(char **arr)
{
	int len = 0;

	while (arr[len])
		len++;
	return (len);
}

/**
 * check_alias - replace command with alias
 * @a: current alias list
 * @t: input tokens
 *
 * Return: 0 if alias was used, 1 otherwise
 */
int check_alias(Alias *a, char ***t)
{
	Alias *temp = search_alias(a, (*t)[0]);
	char **coms = NULL;
	int i, len = 0, len2 = 0;

	if (temp)
	{
		coms = _strtok(strdup(temp->value), " ");
		len = count_tokens(coms);
		len2 = count_tokens(*t);
		if (len > 1)
		{
			*t = realloc(*t, (len2 + len) * sizeof(char *));
			if (!(*t))
				return (1);
			if (len2 > 1)
				memmove(*t + len, *t + 1, (len2 - 1) * sizeof(char *));
			for (i = 0; coms[i]; i++)
				(*t)[i] = coms[i];
			(*t)[len + len2 - 1] = NULL;
		}
		else
			(*t)[0] = coms[0];
		free(coms);
		return (0);
	}
	return (1);
}
