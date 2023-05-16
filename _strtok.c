#include "main.h"

/**
 * _strtok - splits str into tokens using characters in delimiters.
 * @str: the string to split
 * @delimiters: string containing delimiting characters.
 *
 * Return: a pointer to an array of tokens.
 */

char **_strtok(char *str, char *delimiters)
{
	char *temp = NULL, **tokens = NULL;
	int len = 0, i = 0, tokn_strt;

	if (!str)
		return (NULL);
	if (!delimiters)
	{
		tokens = malloc(sizeof(char *) * 2);
		tokens[0] = str;
		tokens[1] = NULL;
		return (tokens);
	}
	len = strlen(str);
	if ((int)strspn(str, delimiters) == len)
		return (NULL);
	temp = strdup(str);
	do
	{
		tokn_strt = strspn(temp, delimiters);
		temp += tokn_strt;
		if (*temp == '\0')
			break;
		tokens = realloc(tokens, sizeof(char *) * (i + 2));
		*(tokens + i) = temp;
		temp = strpbrk(temp, delimiters);
		if (temp)
		{
			*temp = '\0';
			temp++;
		}
		i++;
	} while (temp && *temp);
	free(temp);
	tokens[i] = NULL;
	return (tokens);
}
