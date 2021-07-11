#include "../../includes/minishell.h"

int	compare_variables(char *variable, char *str)
{
	int	i;

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

char	*put_value(char *s, int *i, t_list *list)
{
	char	*variable;
	char	*rez;

	variable = NULL;
	rez = NULL;
	while (s[*i] != 0 && s[*i] != 32 && s[*i] != 34 \
		&& s[*i] != 59 && s[*i] != 36)
	{
		variable = add_one_symbol_in_end(variable, s[*i]);
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
	return (rez);
}

char	*put_variable(char *str, int *i, t_list *list)
{
	char	*rez;

	(*i)++;
	rez = put_value(str, i, list);
	if (rez == NULL)
	{
		rez = put_end_of_string();
		if (rez == NULL)
			return (NULL);
	}
	(*i)--;
	return (rez);
}
