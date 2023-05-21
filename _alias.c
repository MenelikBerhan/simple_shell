#include "main.h"

/**
 * create_alias - create an alias node
 * @key: alias key
 * @value: alias value
 *
 * Return: created alias node
 */
Alias *create_alias(char *key, char *value)
{
	Alias *new_alias = malloc(sizeof(Alias));

	new_alias->key = strdup(key);
	new_alias->value = strdup(value);
	new_alias->next = NULL;
	return (new_alias);
}

/**
 * add_alias - add a new alias to the list
 * @dict: curr alias list
 * @key: new alias key
 * @value: new alias value
 */
void add_alias(Alias **dict, char *key, char *value)
{
	Alias *new_alias = create_alias(key, value);

	new_alias->next = *dict;
	*dict = new_alias;
}

/**
 * search_alias - search for a particular alias node
 * @dict: current alias list
 * @key: search alias key
 *
 * Return: searched alias or NULL
 */
Alias *search_alias(Alias *dict, char *key)
{
	Alias *curr = dict;

	while (curr)
	{
		if (strcmp(curr->key, key) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

/**
 * print_all - print all the available aliases
 * @dict: curr alias list
 */
void print_all(Alias *dict)
{
	Alias *curr = dict;

	while (curr)
	{
		printf("%s='%s'\n", curr->key, curr->value);
		curr = curr->next;
	}
}

/**
 * _alias - handle alias command
 * @sh: shell name
 * @t: input tokens
 * @alias_list: current alias_list
 *
 * Return: process status
 */
int _alias(char *sh, char **t, Alias **alias_list)
{
	Alias *temp;
	char **args;
	int i;

	if (!t[1])
		print_all(*alias_list);
	else
	{
		for (i = 1; t[i]; i++)
		{
			args = _strtok(t[i], "='\"");
			if (args[1])
			{
				temp = search_alias(*alias_list, args[0]);
				if (temp)
				{
					free(temp->value);
					temp->value = strdup(args[1]);
					return (0);
				}
				add_alias(alias_list, args[0], args[1]);
			}
			else
			{
				temp = search_alias(*alias_list, args[0]);
				if (temp)
					printf("%s='%s'\n", temp->key, temp->value);
				else
				{
					fprintf(stderr, "%s: alias: %s: not found\n", sh, args[0]);
					return (1);
				}
			}
			free(args);
		}
	}
	return (0);
}
