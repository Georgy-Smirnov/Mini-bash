#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	check_flags(t_all *all, char *str, int *i)
{
	if (str[*i] == '|')
	{
		all->flags[all->count].pipe = 1;
		return (add_in_struct(all));
	}
	if (str[*i] == '<')
	{
		all->flags[all->count].less_than = 1;
		return (add_in_struct(all));
	}
	if (str[*i] == '>' && str[(*i) + 1] != '>')
	{
		all->flags[all->count].greater_than = 1;
		return (add_in_struct(all));
	}
	if (str[*i] == '>' && str[(*i) + 1] == '>')
	{
		all->flags[all->count].d_greater_than = 1;
		(*i)++;
		return (add_in_struct(all));
	}
	return (1);
}

int	put_arguments(t_all *all, t_list *list, char *str, int *i)
{
	char	*one_arg;

	*i = skip_space(str, *i);
	one_arg = put_end_of_string();
	if (one_arg == NULL)
		return (0);
	while (str[*i] != ' ' && str[*i] != ';' && str[*i] != 0 && \
		str[*i] != '|' && str[*i] != '<' && str[*i] != '>' )
	{
		if (write_one_arg(&one_arg, str, i, list) == 0)
			return (0);
	}
	if (*one_arg != 0)
	{
		one_arg = change_one_arg(one_arg, all, list);
		all->arg[all->count].arguments = \
			add_in_array(all->arg[all->count].arguments, one_arg);
	}
	check_build_in_command(all);
	if (check_flags(all, str, i) == 0)
		return (0);
	free(one_arg);
	return (1);
}

int	do_with_arg(t_all *all, char *str, t_list *list, int *i)
{
	if (put_arguments(all, list, str, i) == 0)
		return (0);
	if (str[*i] == ';')
	{
		if (start_work_command(all, list) == 0)
			return (0);
		clean_struct(all);
		all = create_struct();
	}
	return (1);
}

int	start_parse_command(char *str, t_list *list)
{
	t_all	*all;
	int		i;

	if (check_errors(str) == 0)
		return (1);
	all = create_struct();
	i = skip_space(str, 0);
	while (str[i])
	{
		if (do_with_arg(all, str, list, &i) == 0)
			return (0);
		if (str[i] == 0 || (str[i] == ' ' && str[i + 1] == 0))
		{
			if (start_work_command(all, list) == 0)
				return (0);
			break ;
		}
		i++;
	}
	clean_struct(all);
	return (1);
}
