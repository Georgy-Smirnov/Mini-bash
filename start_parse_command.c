#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return(0);
}

char *skip_space(char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}

void	bzero_t_all(t_all *all)
{
	int i = 0;
	all->com.exp = 0;
	all->com.exp_add = 0;
	all->arg.str = NULL;
	all->com.unset = 0;
	all->com.env = 0;
	all->arg.arguments = NULL;
}

// void	check_build_in_command(t_all *all)
// {
// 	if (!ft_strncmp(all->arg.arguments[0], "unset", 5))
// 		all->com.unset = 1;
// 	if (!ft_strncmp(all->arg.arguments[0], "env", 3))
// 		all->com.env = 1;
// 	if (!ft_strncmp(all->arg.arguments[0], "export", 6))
// 		all->com.exp = 1;
// }

char *add_one_symbol_in_end(char *str, char c)
{
	int i;
	int count;
	char *rez;

	i = 0;
	if (str == NULL)
	{
		rez = (char *)malloc(sizeof(char) * 2);
		if (rez == NULL)
			return (NULL);
		rez[0] = c;
		rez[1] = 0;
	}
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

char	*put_end_of_string()
{
	char *rez;

	rez = (char *)malloc(sizeof(char));
	if (rez == NULL)
		return (0);
	*rez = 0;
	return (rez);
}

int	write_one_arg(char **one_arg, char *str, int *i, t_list *list)
{
	if (str[*i] == '\'')
	{
		*one_arg = add_if_one_quote(*one_arg, str, i);
		if (*one_arg == NULL)
			return (0);
	}
	else if (str[*i] == '"')
	{
		*one_arg = add_if_two_quote(*one_arg, str, i, list);
		if (*one_arg == NULL)
			return (0);
	}
	else if (str[*i] == '"')
	{
		*one_arg = add_one_symbol_in_end(*one_arg, str[(*i) + 1]);
		if (*one_arg == NULL)
			return (0);
		i++;
	}
	else if (str[*i] == '$')
	{
		if (add_if_dollar(str, i, list, one_arg) == 0)
			return (0);
	}
	else
	{
		*one_arg = add_one_symbol_in_end(*one_arg, str[*i]);
		if (*one_arg == NULL)
			return (0);
	}
	if (str[*i] != 0)
		(*i)++;
	return (1);
}

int	start_parse_command(char *str, t_list *list)
{
	int i = 0;
	char *one_arg;
	t_all *all;

	all = (t_all *)malloc(sizeof(t_all));
	if (all == NULL)
		return (0);
	bzero_t_all(all);

	str = skip_space(str);
	while (str[i])
	{
		one_arg = put_end_of_string();
		if (one_arg == NULL)
			return (0);
		while (str[i] != ' ' && str[i] != ';' && str[i] != 0 && str[i] != '|')
		{
			if (write_one_arg(&one_arg, str, &i, list) == 0)
				return (0);
		}
		if (str[i] == ' ')
			str = skip_space(str);
		all->arg.arguments = add_in_array(all->arg.arguments, one_arg);
		free(one_arg);
		one_arg = NULL;
		if (str[i] == ';')
		{
			//ИЗМЕНИТЬ ARGUMENTS
			// check_build_in_command(all);
			if (start_work_command(all, list) == 0)
				return (0);
		}
		if (str[i] == 0)
		{
			if (start_work_command(all, list) == 0)
				return (0);
			break;
		}
		i++;
	}

	i = 0;
	if (all->arg.arguments)
	{
		while (all->arg.arguments[i])
		{
			free(all->arg.arguments[i]);
			i++;
		}
		free(all->arg.arguments);
	}
	free(all);
	return (1);
}