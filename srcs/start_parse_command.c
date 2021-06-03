#include "../includes/minishell.h"

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

char	*put_end_of_string(void)
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

int	check_flags(t_all *all, char *str, int *i)
{
	if (str[*i] == '|')
	{
		all->flags[all->count].pipe = 1;
		if (add_in_struct(all) == 0)
			return (0);
	}
	if (str[*i] == '<')
	{
		all->flags[all->count].less_than = 1;
		if (add_in_struct(all) == 0)
			return (0);
	}
	if (str[*i] == '>' && str[(*i) + 1] != '>')
	{
		all->flags[all->count].greater_than = 1;
		if (add_in_struct(all) == 0)
			return (0);
	}
	if (str[*i] == '>' && str[(*i) + 1] == '>')
	{
		all->flags[all->count].d_greater_than = 1;
		if (add_in_struct(all) == 0)
			return (0);
	}
	return (1);
}

int	put_arguments(t_all *all, t_list *list, char *str, int *i)
{
	char *one_arg;

	*i = skip_space(str, *i);
	one_arg = put_end_of_string();
	if (one_arg == NULL)
		return (0);
	while (str[*i] != ' ' && str[*i] != ';' && str[*i] != 0 && str[*i] != '|' && str[*i] != '<' && str[*i] != '>' )
	{
		if (write_one_arg(&one_arg, str, i, list) == 0)
			return (0);
	}
	if (*one_arg != 0)
		all->arg[all->count].arguments = add_in_array(all->arg[all->count].arguments, one_arg);
	if (check_flags(all, str, i) == 0)
		return (0);
	free(one_arg);
	return (1);
}

int	start_parse_command(char *str, t_list *list)
{
	int i = 0;
	int j= 0;
	char *one_arg;
	t_all *all;

	if (check_errors(str) == 0)
		return (1);
	all = create_struct();
	while (str[i])
	{
		if (put_arguments(all, list, str, &i) == 0)
			return (0);
		if (str[i] == ';')
		{
			if (start_work_command(all, list) == 0)
				return (0);
			clean_struct(all);
			all = create_struct();
		}
		if (str[i] == 0)
		{
			if (start_work_command(all, list) == 0)
				return (0);
			break;
		}
		i++;
	}
	clean_struct(all);
	return (1);
}