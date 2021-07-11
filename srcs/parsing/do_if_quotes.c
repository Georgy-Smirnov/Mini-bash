#include "../../includes/minishell.h"

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

char *search_variable(char *str)
{
	char *variable;
	int i;
	
	i = 0;
	variable = put_end_of_string();
	while (str[i] != '$')
		i++;
	while (str[i] != 0 && str[i] != ' ' && str[i] != '"')
	{
		variable = add_one_symbol_in_end(variable, str[i]);
		if (variable == NULL)
			return (NULL);
		i++;
	}
	return (variable);
}

char *add_if_two_quote(char *one_arg, char *str, int *i, t_list *list)
{
	char *rez;
	char *tmp;
	char *tmp2;

	(*i)++;
	rez = one_arg;
	while (str[*i] != 0 && str[*i] != '"')
	{
		if (str[*i] == '\\')
		{
			if (str[(*i) + 1] == '$' || str[(*i) + 1] == '\\' || str[(*i) + 1] == '"')
			{
				rez = add_one_symbol_in_end(rez, str[(*i) + 1]);
				if (rez == NULL)
					return (NULL);
				(*i) += 2;
			}
			else
			{
				rez = add_one_symbol_in_end(rez, str[*i]);
				(*i)++;
			}
		}
		else if (str[*i] == '$')
		{
			if (add_if_dollar(str, i, list, &rez) == 0)
				return (NULL);
			(*i)++;
		}
		else
		{
			rez = add_one_symbol_in_end(rez, str[*i]);
			if (rez == NULL)
				return (NULL);
			(*i)++;
		}
	}
	return (rez);
}

int	compare_variables(char *variable, char *str)
{
	int i;

	i = 0;
	while (variable[i])
	{
		if (variable[i] != str[i])
			return (0);
		i++;
	}
	if (str[i] != '=')
		return (0);
	return (1);
}

char *put_variable(char *str, int *i, t_list *list)
{
	char *variable;
	char *rez;
	char *max;

	(*i)++;
	rez = NULL;
	variable = put_end_of_string();
	if (variable == NULL)
		return (NULL);
	while (str[*i] != 0 && str[*i] != ' ' && str[*i] != '"' && str[*i] != ';'  && str[*i] != '$')
	{
		variable = add_one_symbol_in_end(variable, str[*i]);
		if (variable == NULL)
			return (NULL);
		(*i)++;
	}
	while (list != NULL)
	{
		if (compare_variables(variable, list->content) == 1)
		{
			rez = ft_strdup(&list->content[ft_strlen(variable) + 1]);
			if (rez == NULL)
				return (NULL);
			free(variable);
		}
		list = list->next;
	}
	if (rez == NULL)
	{
		rez = put_end_of_string();
		if (rez == NULL)
			return (NULL);
	}
	(*i)--;
	return (rez);
}

int	add_if_dollar(char *str, int *i, t_list *list, char **one_arg)
{
	char *tmp;

	tmp = put_variable(str, i, list);
	if (tmp == NULL)
		return (0);
	*one_arg = ft_strjoin_with_frees1(*one_arg, tmp);
	if (*one_arg == NULL)
		return (0);
	free(tmp);
	return (1);
}