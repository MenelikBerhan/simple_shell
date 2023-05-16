# include "main.h"

/**
 * _strtok - splits str into tokens using characters in delimiters.
 * @str: the string to split
 * @delimiters: string containing delimiting characters.
 *
 * Return: a pointer to an array of tokens.
*/

char **_strtok(char *str, char *delimiters) /* add int len argument incase there is null char in str other than the terminating one */
{
	char *temp, **tokens = NULL;
	int len = 0, i = 0, tokn_strt;

	if (!str)
		return (NULL);
	if (!delimiters)
	{
		tokens = realloc(tokens, sizeof(char *) * (i + 2));
		tokens[0] = str;
		tokens[1] = NULL;
		return (tokens);
	}
	len = strlen(str);
	if ((int) strspn(str, delimiters) == len)
		return (NULL);

	temp = strdup(str); /* since string will be modified copy and free *tokens in calling function */

	do {
		tokn_strt = strspn(temp, delimiters);
		temp += tokn_strt;
		if (*temp == '\0') /* use len to check if end is reached when null chars in the middle */
			break;

		tokens = realloc(tokens, sizeof(char *) * (i + 2)); /* +2 one for the token one for null */
		*(tokens + i) = temp;

		temp = strpbrk(temp, delimiters);

		if (temp)
		{
			*temp = '\0';
			temp++;
		}
		i++;
	} while (temp && *temp);

	tokens[i] = NULL;

	return (tokens); /* when finished in calling fun free *tokens and tokens */
}
