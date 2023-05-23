#include "main.h"

/**
 * handle_comment - removes the part of a string after '#' that are
 * on the same line, unless # is preceeded by a non-blank character.
 * @str: string operand.
 *
*/
void handle_comment(char *str)
{
	int i, len, temp_i;

	len = strlen(str);
	for (i = 0; i < len; i++)
	{
		if (str[i] == '\"')
		{
			temp_i = i++;
			while (str[i] != '\"' && str[i] != '\n' && i < len)
				i++;
			if (i < len && str[i] == '"')
				continue;
			else
				i = temp_i;
		}

		if (str[i] == '#' && (i == 0 || str[i - 1] == '\n' || str[i - 1] == ' '))
		{
			while (str[i] != '\n' && i < len)
				str[i++] = '\0';
		}
	}
	for (i = 0; i < len; i++)
	{
		if (str[i] == '\0')
		{
			temp_i = i++;
			while (str[i] == '\0' && i < len)
				i++;
			str[temp_i] = str[i];
			str[i] = '\0';
			i = temp_i;
		}
	}
}

/**
 * expansion_helper - handles expansions for $?, $$ or when there is a digit
 * after $ in string pointed by str.
 * @str: pointer to the string
 * @temp: poiinter to a temporary string
 * @i: pointer to current index
 * @remove_len: length of characters to remove after expansion
 * @p_s: return or exit status of previously executed program
 *
 * Return: 1 if the loop should continue, or 0 otherwise.
*/
int expansion_helper(char **str, char **temp, int *i, int *remove_len, int p_s)
{
	char *e = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_?$";
	char *n = "0123456789";

	if (!strspn((*str) + *i + 1, e))
	{
		if (strspn((*str) + *i + 1, n))
		{
			*remove_len = 2;
			*temp = "";
		}
		else
		{
			i++;
			return (1);
		}
	}
	else if ((*str)[*i + 1] == '?')
	{
		*remove_len = 2;
		sprintf(*temp, "%d", p_s);
	}
	else if ((*str)[*i + 1] == '$')
	{
		*remove_len = 2;
		sprintf(*temp, "%d", getpid());
	}
	return (0);
}



/**
 * handle_expansion - expands variable names preceeded by '$' in a string.
 * @line: pointer to the string operand
 * @prev_status: exit status or return of previously excuted program
 *
 * Return: the expanded string.
*/
char *handle_expansion(char **line, int prev_status)
{
	int i, j, len, add_len, remove_len, to_nxt_space, name_alloced = 0;
	char *e = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_?$";
	char *temp, *name, *str;

	str = *line;
	len = strlen(str);
	for (i = 0; i < len; i++)
	{
		if (str[i] == '$')
		{
			if (!strspn(str + i + 1, e) || str[i + 1] == '?' || str[i + 1] == '$')
			{
				if (expansion_helper(&str, &temp, &i, &remove_len, prev_status))
					continue;
			}
			else
			{
				to_nxt_space = strcspn(str + i + 1, " ");
				if (name_alloced)
					free(name);
				name = strndup(str + i + 1, to_nxt_space);
				name_alloced = 1;
				temp = _getenv(name);
				remove_len = to_nxt_space + 1;
			}
			temp = temp ? temp : "";
			add_len = strlen(temp);
			if (add_len > remove_len)
				str = realloc(str, (len + 1 + (add_len - remove_len)));
			memmove((str + i + add_len), (str + i + remove_len)
				, len + 1 - (i + remove_len));
			for (j = 0 ; j < add_len; j++)
				str[i + j] = temp[j];
			len = strlen(str);
			i = i + add_len;
		}
	}
	if (name_alloced)
		free(name);
	return (str);
}
