#include "../../includes/minishell.h"

void	another_com(t_all *all, int i)
{
	pid_t	pid;
	int		status;
	int		rez;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		dup_fd(all, i);
		execve(all->arg[i].arguments[0], all->arg[i].arguments, NULL);
	}
	else
	{
		if (wait(0) == -1)
			perror("wait() error");
		else if (WIFEXITED(status))
			rez = WEXITSTATUS(status);
	}
	close_fd(all, i);
}
