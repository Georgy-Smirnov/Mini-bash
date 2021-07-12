#include "minishell.h"

void	output_with_equal(char *str, int i)
{
	ft_putstr_fd("declare -x ", 1);
	while (str[i] != '=' && str[i])
		write(1, &str[i++], 1);
	if (str[i] == '=')
		write(1, &str[i++], 1);
	write(1, "\"", 1);
	while (str[i])
		write(1, &str[i++], 1);
	write(1, "\"", 1);
	write(1, "\n", 1);
	i = 0;
}

void	output_export(t_list *list)
{
	t_list	*copy;
	int		i;

	copy = list->next;
	i = 0;
	while (copy != NULL)
	{
		if (ft_strchr(copy->content, '='))
			output_with_equal(copy->content, i);
		else
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(copy->content, 1);
			write(1, "\n", 1);
		}
		copy = copy->next;
	}
}

void	sort_export(t_list *list, t_all *all, int i)
{
	t_list	*copy;
	t_list	*next;

	dup_fd(all, i);
	copy = list->next;
	next = list->next->next;
	while (copy->next != NULL)
	{
		while (next->next != NULL)
		{
			all->n.str1 = (char *)(copy->content);
			all->n.str2 = (char *)(next->content);
			if (ft_strcmp(all->n.str1, all->n.str2) > 0)
			{
				all->n.tmp = all->n.str1;
				copy->content = all->n.str2;
				next->content = all->n.tmp;
			}
			next = next->next;
		}
		copy = copy->next;
		next = copy;
	}
	output_export(list);
	close_fd(all, i);
}
