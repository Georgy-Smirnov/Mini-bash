#include "../../includes/minishell.h"

void	get_pwd(t_all *all, int i)
{
	char	*buf;

	dup_fd(all, i);
	buf = malloc(100000);
	if (!(buf))
		return ;
	getcwd(buf, 100000);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
	close_fd(all, i);
}
