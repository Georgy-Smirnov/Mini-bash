#include "../../includes/minishell.h"

int	exist_value_env(t_all *all, t_list *list, char *value)
{
	t_list	*copy;
	char	*str;
	int		i;

	copy = list;
	i = 0;
	all->nor.unset_i = 0;
	all->nor.unset_j = 0;
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
	t_list	*copy;
	t_list	*before;
	t_list	*after;

	copy = list;
	if (exist_value_env(all, list, all->arg->arguments[all->i]))
	{
		while (copy->next != NULL)
		{
			copy = copy->next;
			if (!(ft_strncmp(copy->content, all->arg->arguments[all->i], \
				ft_strlen(all->arg->arguments[all->i]))))
				break ;
			all->nor.unset_i++;
		}
		after = copy->next;
		before = list->next;
		while (all->nor.unset_j++ != (all->nor.unset_i - 1))
			before = before->next;
		free(copy);
		if (before->next != NULL)
			before->next = after;
	}
}
