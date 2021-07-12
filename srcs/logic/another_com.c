#include "minishell.h"

void	another_com(t_all *all, int i)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid == -1)
	{
		exit(1);
	}
	else if (pid == 0)
	{
		dup_fd(all, i);
		execve(all->arg[i].arguments[0], all->arg[i].arguments, NULL);
	}
	else
	{
		wait(&wstatus);
		if (WIFEXITED(wstatus))
			g_err = WEXITSTATUS(wstatus);
	}
	close_fd(all, i);
}
