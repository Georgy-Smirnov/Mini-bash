#include "minishell.h"

int	get_len_name(t_all *all)
{
	int	i;

	i = 0;
	if ((ft_strchr(all->arg->arguments[all->i], '=') != NULL))
	{
		while (all->arg->arguments[all->i][i] != '=')
			i++;
	}
	else
	{
		while (all->arg->arguments[all->i][i] != '\0')
			i++;
	}
	return (i);
}

void	print_err(t_all *all)
{
	write(1, "Minishell: export: '", 20);
	write(1, all->arg->arguments[all->i], \
		ft_strlen(all->arg->arguments[all->i]));
	write(1, "': not a valid identifier\n", 26);
	g_err = 1;
}

void	add_value(t_list *list, t_all *all)
{
	t_list	*copy;

	copy = list;
	while (copy != NULL)
	{
		if (!(ft_strncmp(copy->content, all->arg->arguments[all->i], \
		get_len_name(all))))
		{
			free(copy->content);
			copy->content = ft_strdup(all->arg->arguments[all->i]);
			list = copy;
			all->n.flag = 0;
			break ;
		}
		copy = copy->next;
	}
}

void	add_export(t_list *list, t_all *all)
{
	all->n.flag = 1;
	while (all->arg->arguments[all->i] != NULL)
	{
		if (ft_isalpha(all->arg->arguments[all->i][0]))
		{
			add_value(list, all);
			if (all->n.flag)
				ft_lstadd_back(&list, \
				ft_lstnew(ft_strdup(all->arg->arguments[all->i])));
		}
		else
			print_err(all);
		all->i++;
	}
}
