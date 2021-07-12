#include "minishell.h"

int	skip_space(char *str, int i)
{
	while (str[i] == ' ')
	{
		i++;
	}
	return (i);
}

int	print_error(void)
{
	write(1, "Syntax error!\n", 14);
	return (0);
}

int	cicle(int *i, int *j, char *str, char *last_char)
{
	while (str[*i])
	{
		if (str[*i] != ';' && str[*i] != '|' && str[*i] != '<')
			if (str[*i] != '>' && str[*i] != ' ')
				(*j)++;
		if (str[*i] == 59 || str[*i] == '|' || str[*i] == 60 || str[*i] == 62)
		{
			if ((*j) == 0)
			{
				if (str[*i] == '>' && str[*i - 1] == '>' && str[*i + 1] != '>')
					(*i)++;
				else
					return (0);
			}
			*last_char = str[*i];
			(*j) = 0;
		}
		(*i)++;
	}
	return (1);
}

int	check_errors(char *str)
{
	int		i;
	int		j;
	char	last_char;

	i = 0;
	j = 0;
	i = skip_space(str, i);
	if (str[i] == 0)
		return (1);
	if (str[i] == ';' || str[i] == '|' || str[i] == '<' || str[i] == '>')
		return (print_error());
	if (cicle(&i, &j, str, &last_char) == 0)
		return (print_error());
	if (j == 0 && last_char != ';')
		return (print_error());
	if (str[i - 1] == '\\')
		return (print_error());
	return (1);
}
