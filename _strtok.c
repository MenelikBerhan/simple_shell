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
	char *token, **tokens, **resizedTokens;
	int foundDelimiter = 0;
	size_t tokenCount = 0, maxTokens = 10;

	if (!str || (delimiters && (strspn(str, delimiters) == strlen(str))))
		return (NULL);
	tokens = malloc((maxTokens + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	if (!delimiters)
	{
		tokens[0] = strdup(str);
		tokens[1] = NULL;
		return (tokens);
	}
	str += strspn(str, delimiters);
	while (*str != '\0')
	{
		token = str;
		str += strcspn(str, delimiters);
		foundDelimiter = (*str != '\0');
		if (foundDelimiter)
			*str++ = '\0';
		tokens[tokenCount++] = token;
		if (tokenCount >= maxTokens)
		{
			maxTokens *= 2;
			resizedTokens = realloc(tokens, (maxTokens + 1) * sizeof(char *));
			if (resizedTokens == NULL)
			{
				free(tokens);
				return (NULL);
			}
			tokens = resizedTokens;
		}
	}
	tokens[tokenCount] = NULL;
	return (tokens);
}
