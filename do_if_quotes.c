#include "minishell.h"

char *add_if_one_quote(char *one_arg, char *str, int *i)
{
	char *rez;

	(*i)++;
	rez = one_arg;
	while (str[*i] != 0 && str[*i] != '\'')
	{
		rez = add_one_symbol_in_end(rez, str[*i]);
		if (rez == NULL)
			return (NULL);
		(*i)++;
	}
	return (rez);
}

char *add_if_two_quote(char *one_arg, char *str, int *i)
{
	char *rez;

	(*i)++;
	rez = one_arg;
	while (str[*i] != 0 && str[*i] != '\'')
	{
		rez = add_one_symbol_in_end(rez, str[*i]);
		if (rez == NULL)
			return (NULL);
		(*i)++;
	}
	return (rez);
}

char *add_if_dollar(char *one_arg, char *str, int *i)
{
	char *rez;

	(*i)++;
	rez = one_arg;
	while (str[*i] != 0 && str[*i] != '\'')
	{
		rez = add_one_symbol_in_end(rez, str[*i]);
		if (rez == NULL)
			return (NULL);
		(*i)++;
	}
	return (rez);
}