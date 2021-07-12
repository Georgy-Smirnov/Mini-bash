#include "minishell.h"

void	ft_echo(t_all *all, int i)
{
	int	j;

	j = 1;
	dup_fd(all, i);
	while (all->arg[i].arguments[j])
	{
		write(1, all->arg[i].arguments[j], ft_strlen(all->arg[i].arguments[j]));
		write(1, " ", 1);
		j++;
	}
	write (1, "\n", 1);
	close_fd(all, i);
	g_err = 0;
}
