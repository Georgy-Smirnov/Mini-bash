#include "minishell.h"

void	check_build_in_command(t_all *all)
{
	if (!ft_strncmp(all->arg[all->count].arguments[0], "export", 6) \
		&& all->arg[all->count].arguments[1] == NULL)
		all->com[all->count].exp = 1;
	else if (!ft_strncmp(all->arg[all->count].arguments[0], "export", 6))
	{
		all->com[all->count].exp = 0;
		all->com[all->count].exp_add = 1;
	}
	else if (!ft_strncmp(all->arg[all->count].arguments[0], "unset", 5))
		all->com[all->count].unset = 1;
	else if (!ft_strncmp(all->arg[all->count].arguments[0], "env", 3))
		all->com[all->count].env = 1;
	else if (!ft_strncmp(all->arg[all->count].arguments[0], "cd", 2))
		all->com[all->count].cd = 2;
	else if (!ft_strncmp(all->arg[all->count].arguments[0], "pwd", 3))
		all->com[all->count].pwd = 1;
	else if (!ft_strncmp(all->arg[all->count].arguments[0], "exit", 4))
		all->com[all->count].exit = 1;
	else if (!ft_strncmp(all->arg[all->count].arguments[0], "echo", 4))
	{
		all->com[all->count].echo = 1;
		if (all->arg[all->count].arguments[1] != NULL && \
			!ft_strncmp(all->arg[all->count].arguments[1], "-n", 2))
			all->com[all->count].n = 1;
	}
}

int	open_fd(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->count)
	{
		if (work_with_fd(all, i) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	start_work_command(t_all *all, t_list *list)
{
	if (open_fd(all) == 0)
		return (0);
	parse_command(all, list);
	return (1);
}
