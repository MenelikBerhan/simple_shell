#include "main.h"

/**
 * _strtok - splits string str into tokens using characters in delimiters.
 * @str: the string to split
 * @delim: string containing delimiting characters.
 *
 * Return: a pointer to an array of tokens.
 */
char **_strtok(char *str, char *delim)
{
	char *token, **tokens;
	int foundDelimiter = 0;
	size_t tokenCount = 0, maxTokens = 10;

	if (!str || (delim && (strspn(str, delim) == strlen(str))))
		return (NULL);
	tokens = malloc((maxTokens + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	str += strspn(str, delim);
	while (*str != '\0')
	{
		token = str;
		if (!strcspn(str++, delim))
			continue;
		if (strchr(delim, ' ') && strcspn(str, "\"'") < strcspn(str, delim))
		{
			str += strcspn(str, "\"'") + 1;
			str += strcspn(str, "\"'");
			str += strcspn(str, delim);
		}
		else
			str += strcspn(str, delim);
		foundDelimiter = (*str != '\0');
		if (foundDelimiter)
			*str++ = '\0';
		tokens[tokenCount++] = token;
		if (tokenCount >= maxTokens)
		{
			maxTokens *= 2;
			tokens = realloc(tokens, (maxTokens + 1) * sizeof(char *));
			if (tokens == NULL)
				return (NULL);
		}
	}
	tokens[tokenCount] = NULL;
	return (tokens);
}
