#include "../../includes/minishell.h"

void	dup_fd(t_all *all, int i)
{
	all->tmp_fd1 = dup(1);
	all->tmp_fd0 = dup(0);
	printf("");
	dup2(all->arg[i].fd[1], 1);
	dup2(all->arg[i].fd[0], 0);
}

void	close_fd(t_all *all, int i)
{
	if (all->arg[i].fd[0] != 0)
		close(all->arg[i].fd[0]);
	if (all->arg[i].fd[1] != 1)
		close(all->arg[i].fd[1]);
	dup2(all->tmp_fd1, 1);
	dup2(all->tmp_fd0, 0);
}
