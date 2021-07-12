#include "minishell.h"

char	*create_rez(char c)
{
	char	*rez;

	rez = (char *)malloc(sizeof(char) * 2);
	if (rez == NULL)
		return (NULL);
	rez[0] = c;
	rez[1] = 0;
	return (rez);
}

char	*add_one_symbol_in_end(char *str, char c)
{
	int		i;
	int		count;
	char	*rez;

	i = 0;
	if (str == NULL)
		rez = create_rez(c);
	else
	{
		count = ft_strlen(str);
		rez = (char *)malloc(sizeof(char) * (count + 2));
		if (rez == NULL)
			return (NULL);
		while (str[i])
		{
			rez[i] = str[i];
			i++;
		}
		rez[i] = c;
		rez[i + 1] = 0;
		free(str);
	}
	return (rez);
}

int	write_one_arg(char **one_arg, char *str, int *i, t_list *list)
{
	if (str[*i] == '\'')
		*one_arg = add_if_one_quote(*one_arg, str, i);
	else if (str[*i] == '"')
		*one_arg = add_if_two_quote(*one_arg, str, i, list);
	else if (str[*i] == '"')
	{
		*one_arg = add_one_symbol_in_end(*one_arg, str[(*i) + 1]);
		i++;
	}
	else if (str[*i] == '$')
	{
		if (add_if_dollar(str, i, list, one_arg) == 0)
			return (0);
	}
	else
		*one_arg = add_one_symbol_in_end(*one_arg, str[*i]);
	if (*one_arg == NULL)
		return (0);
	if (str[*i] != 0)
		(*i)++;
	return (1);
}
