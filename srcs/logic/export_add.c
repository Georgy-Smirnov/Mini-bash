#include "../../includes/minishell.h"

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

void	add_export(t_list *list, t_all *all)
{
	t_list	*copy;

	all->n.flag = 1;
	while (all->arg->arguments[all->i] != NULL)
	{
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
		if (all->n.flag)
			ft_lstadd_back(&list, \
			ft_lstnew(ft_strdup(all->arg->arguments[all->i])));
		all->i++;
	}
}
