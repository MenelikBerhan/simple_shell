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
 * @r_len: length of characters to remove after expansion
 * @p_s: return or exit status of previously executed program
 *
 * Return: 1 if the loop should continue, or 0 otherwise.
 */
int expansion_helper(char **str, char **temp, int *i, int *r_len, int p_s)
{
	char *e = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_?$";
	char *n = "0123456789";

	if (!strspn((*str) + *i + 1, e))
	{
		if (strspn((*str) + *i + 1, n))
		{
			*r_len = 1;
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
		*r_len = 2;
		snprintf(*temp, 16, "%d", p_s);
	}
	else if ((*str)[*i + 1] == '$')
	{
		*r_len = 2;
		snprintf(*temp, 16, "%d", getpid());
	}
	return (0);
}

/**
 * handle_expansion - expands variable names preceeded by '$' in a string.
 * @str: pointer to the string operand
 * @prev_status: exit status or return of previously excuted program
 *
 * Return: the expanded string.
 */
char *handle_expansion(char *str, int prev_status)
{
	int i, j, len, a_len, r_len, t_n_sp, is_name = 0;
	char *e = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_?$";
	char *temp, *name;

	len = strlen(str);
	for (i = 0; i < len; i++)
	{
		if (str[i] == '$')
		{
			if (!strspn(str + i + 1, e) || str[i + 1] == '?' || str[i + 1] == '$')
			{
				if (expansion_helper(&str, &temp, &i, &r_len, prev_status))
					continue;
			}
			else
			{
				t_n_sp = strcspn(str + i + 1, " ");
				if (is_name)
					free(name);
				name = strndup(str + i + 1, t_n_sp);
				is_name = 1;
				temp = _getenv(name);
				r_len = t_n_sp + 1;
			}
			temp = temp ? temp : "";
			a_len = strlen(temp);
			if (a_len > r_len)
				str = realloc(str, (len + 1 + (a_len - r_len)));
			memmove((str + i + a_len), (str + i + r_len), len + 1 - (i + r_len));
			for (j = 0; j < a_len; j++)
				str[i + j] = temp[j];
			len = strlen(str);
			i = i + a_len;
		}
	}
	if (is_name)
		free(name);
	return (str);
}
