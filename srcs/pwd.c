#include "../includes/minishell.h"

void	get_pwd(t_all *all)
{
	char *buf;

	if (!(buf = malloc(100000)))
		return ;
	getcwd(buf, 100000);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
}