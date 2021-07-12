#include "minishell.h"

void	print_er(t_all *all, int i)
{
	write(1, "env: ", 5);
	write(1, all->arg[i].arguments[1], ft_strlen(all->arg[i].arguments[1]));
	write(1, ": No such file or directory\n", 28);
	g_err = 127;
}

void	output_list(t_list *list, t_all *all, int i)
{
	if (all->arg[i].arguments[1] == NULL)
	{
		dup_fd(all, i);
		while (list->next != NULL)
		{
			list = list->next;
			if (ft_strchr(list->content, '='))
				printf("%s\n", list->content);
		}
		close_fd(all, i);
		g_err = 0;
	}
	else
		print_er(all, i);
}
