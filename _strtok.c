#include "main.h"

/**
 * _strtok - splits string str into tokens using characters in delimiters.
 * @str: the string to split
 * @delimiters: string containing delimiting characters.
 *
 * Return: a pointer to an array of tokens.
 * Note: the caller must free *tokens before freeing tokens.
 */
char **_strtok(char *str, char *delimiters)
{
	char *temp = NULL, **tokens = NULL;
	int i = 0, maxTokens = 10;

	if (!str || (delimiters && (strspn(str, delimiters) == strlen(str))))
		return (NULL);
	tokens = malloc(sizeof(char *) * (maxTokens + 1));
	if (!delimiters)
	{
		tokens[0] = strdup(str);
		tokens[1] = NULL;
		return (tokens);
	}
	str += strspn(str, delimiters);
	temp = strdup(str);
	tokens[i++] = temp;
	while ((temp = strpbrk(temp, delimiters)) && *temp)
	{
		*temp = 0;
		temp++;
		temp += strspn(temp, delimiters);
		if (*temp)
		{
			if (i == maxTokens)
			{
				maxTokens *= 2;
				tokens = realloc(tokens, sizeof(char *) * (maxTokens + 1));
			}
			tokens[i++] = temp;
		}
		else
			break;
	}
	tokens[i] = NULL;
	return (tokens);
}
