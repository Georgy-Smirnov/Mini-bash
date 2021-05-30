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

char *put_variable(char *str)
{
	int j = 0;
	
	char *rez;
	while (str[j] != '$')
		j++;
	j++;
	while (str[j] != 0 && str[j] != ' ' && str[j] != '"')
	{
		rez = add_one_symbol_in_end(rez, str[j]);
		if (rez == NULL)
			return (NULL);
		j++;
	}
	return (rez);
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
				rez = add_one_symbol_in_end(rez, str[(*i) + 1]);
				//CHECK NULL
			(*i) += 2;
		}
		else if (str[*i] == '$')
		{
			printf("==%d==%c==\n", *i, str[*i]);
			tmp = add_if_dollar(&str[(*i) - 1], i, list);
			//check NUll
			rez = ft_strjoin_with_frees1(rez, tmp);
			//check NULL
			printf("___%d___%s___\n", *i, tmp);
			*i += ft_strlen(tmp);
			free(tmp);
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

char *add_if_dollar(char *str, int *i, t_list *list)
{
	char *variable;
	char *rez = NULL;

	printf("==%d==%c==\n", *i, str[*i]);
	(*i)++;
	variable = put_end_of_string();
	while (str[*i] != 0 && str[*i] != ' ' && str[*i] != '"')
	{
		variable = add_one_symbol_in_end(variable, str[*i]);
		if (variable == NULL)
			return (NULL);
		(*i)++;
	}
	printf(">>>%s<<<", variable);
	while (list->next)
	{
		if (ft_strncmp(list->content, variable, (size_t)ft_strlen(variable)) == 0)
			rez = ft_strdup(list->content+=(ft_strlen(variable) + 1));
			//check NULL
		list = list->next;
	}
	(*i)--;
	return (rez);
}