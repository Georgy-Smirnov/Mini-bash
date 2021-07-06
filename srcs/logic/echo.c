#include "../../includes/minishell.h"

void	ft_echo(t_all *all, int i)
{
	int	j;

	j = 1;
	while (all->arg[i].arguments[j])
	{
		write(1, all->arg[i].arguments[j], ft_strlen(all->arg[i].arguments[j]));
		write(1, " ", 1);
		j++;
	}
	write (1, "\n", 1);
}
