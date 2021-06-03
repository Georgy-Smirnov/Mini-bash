#include "minishell.h"

int	skip_space(char *str, int i)
{
	while (str[i] == ' ')
	{
		i++;
	}
	return (i);
}

int	skip_right_symbol(char *str, int i, int *tmp_i)
{
	while (str[i] != ';' && str[i] != '|' && str[i] != '<' && str[i] != '>')
	{
		i++;
		(*tmp_i)++;
	}
	if (str[i] == '>' && str[i + 1] == '>' &&
	str[i - 1] != '>'  && str[i + 2] != '>')
	{
		*tmp_i = 1;
		i++;
	}
	return (i);
}

int	check_errors(char *str)
{
	int i;
	int tmp_i;

	i = 0;
	i = skip_space(str, i);
	if (str[i] == ';' || str[i] == '|' || str[i] == '<' || str[i] == '>')
	{
		ft_putstr_fd("Syntax error!\n", 1);
		return (0);
	}
	while (str[i])
	{
		tmp_i = 0;
		i = skip_space(str, i);
		i = skip_right_symbol(str, i, &tmp_i);
		if (tmp_i == 0)
		{
			ft_putstr_fd("Syntax error!\n", 1);
			return (0);	
		}
		i++;
	}
	if (str[i - 1] == '\\')
	{
		ft_putstr_fd("Syntax error!\n", 1);
		return (0);	
	}
	return (1);
}