#include "../../includes/minishell.h"

char	*add_if_one_quote(char *one_arg, char *str, int *i)
{
	char	*rez;

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

int	do_if_backslash(char **rez, char *str, int *i)
{
	if (str[(*i) + 1] == '$' || str[(*i) + 1] == '\\' || str[(*i) + 1] == '"')
	{
		*rez = add_one_symbol_in_end(*rez, str[(*i) + 1]);
		if (*rez == NULL)
			return (0);
		(*i) += 2;
	}
	else
	{
		*rez = add_one_symbol_in_end(*rez, str[*i]);
		(*i)++;
	}
	return (1);
}

int	do_in_circle(char **rez, char *str, int *i, t_list *list)
{
	if (str[*i] == '\\')
	{
		if (do_if_backslash(rez, str, i) == 0)
			return (0);
	}
	else if (str[*i] == '$')
	{
		if (add_if_dollar(str, i, list, rez) == 0)
			return (0);
		(*i)++;
	}
	else
	{
		*rez = add_one_symbol_in_end(*rez, str[*i]);
		if (*rez == NULL)
			return (0);
		(*i)++;
	}
	return (1);
}

char	*add_if_two_quote(char *one_arg, char *str, int *i, t_list *list)
{
	char	*rez;

	(*i)++;
	rez = one_arg;
	while (str[*i] != 0 && str[*i] != '"')
	{
		if (do_in_circle(&rez, str, i, list) == 0)
			return (NULL);
	}
	return (rez);
}

int	add_if_dollar(char *str, int *i, t_list *list, char **one_arg)
{
	char	*tmp;

	tmp = put_variable(str, i, list);
	if (tmp == NULL)
		return (0);
	*one_arg = ft_strjoin_with_frees1(*one_arg, tmp);
	if (*one_arg == NULL)
		return (0);
	free(tmp);
	return (1);
}
