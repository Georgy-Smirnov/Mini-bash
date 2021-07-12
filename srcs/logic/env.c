#include "minishell.h"

void	output_list(t_list *list, t_all *all, int i)
{
	dup_fd(all, i);
	while (list->next != NULL)
	{
		list = list->next;
		if (ft_strchr(list->content, '='))
			printf("%s\n", list->content);
	}
	close_fd(all, i);
}
