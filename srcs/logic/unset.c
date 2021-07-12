#include "minishell.h"

int	exist_value_env(t_all *all, t_list *list, char *value)
{
	t_list	*copy;
	char	*str;
	int		i;

	all->n.unset_i = 0;
	all->n.unset_j = 0;
	copy = list;
	i = 0;
	all->n.l = ft_strlen(all->arg->arguments[all->i]);
	while (copy->next != NULL)
	{
		copy = copy->next;
		str = (char *)copy->content;
		while (str[i] != '=' && str[i] && value[i])
		{
			if (str[i] == value[i])
				i++;
			else
				break ;
		}
		if (ft_strlen(value) == i)
			return (1);
		i = 0;
	}
	return (0);
}

void	unset(t_list *list, t_all *all)
{
	t_list	*c;
	t_list	*before;
	t_list	*after;

	c = list;
	if (exist_value_env(all, list, all->arg->arguments[all->i]))
	{
		while (c->next != NULL)
		{
			c = c->next;
			if (!ft_strncmp(c->content, all->arg->arguments[all->i], all->n.l))
			{
				free(c->content);
				break ;
			}
			all->n.unset_i++;
		}
		after = c->next;
		before = list->next;
		while (all->n.unset_j++ != (all->n.unset_i - 1))
			before = before->next;
		free(c);
		if (before->next != NULL)
			before->next = after;
	}
}
