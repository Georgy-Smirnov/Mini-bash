#include "minishell.h"

void echo_n(t_all *all, int i)
{
	int	j;

	j = 2;
	while (all->arg[i].arguments[j])
	{
		write(1, all->arg[i].arguments[j], ft_strlen(all->arg[i].arguments[j]));
		j++;
		if (all->arg[i].arguments[j] != NULL)
			write(1, " ", 1);
	}
}

void	ft_echo(t_all *all, int i)
{
	int	j;

	j = 1;
	dup_fd(all, i);
	if (ft_strcmp(all->arg[i].arguments[j], "-n"))
	{
		while (all->arg[i].arguments[j])
		{
			write(1, all->arg[i].arguments[j], ft_strlen(all->arg[i].arguments[j]));
			j++;
			if (all->arg[i].arguments[j] != NULL)
				write(1, " ", 1);
		}
		write (1, "\n", 1);
	}
	else
		echo_n(all, i);
	close_fd(all, i);
	g_err = 0;
}
