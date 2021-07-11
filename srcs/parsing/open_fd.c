#include "../../includes/minishell.h"

int	count_symbol(char *str, int *q)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '/')
		{
			count = 0;
			(*q) = i;
		}
		count++;
		i++;
	}
	return (count);
}

char	*if_slash(char *str)
{
	char	*rez;
	int		count;
	int		i;
	int		q;

	i = 0;
	count = count_symbol(str, &q);
	rez = (char *)malloc(sizeof(char) * count + 1);
	if (rez == NULL)
		return (rez);
	q++;
	while (str[q])
	{
		rez[i] = str[q];
		i++;
		q++;
	}
	rez[i] = 0;
	return (rez);
}

char	*put_name_file(char *str)
{
	char	*rez;
	int		i;
	int		q;
	int		count;

	i = 0;
	count = 0;
	if (str[0] == '/')
	{
		return (if_slash(str));
	}
	else
	{
		rez = ft_strdup(str);
		return (rez);
	}
}

int	do_if_greater_less(t_all *all, int *fd, char *tmp_str, int i)
{
	if (all->flags[i].greater_than)
	{
		if (*fd != -2)
			close(*fd);
		*fd = open(tmp_str, O_CREAT | O_RDWR | O_TRUNC, 0777);
		all->arg[i].fd[1] = *fd;
	}
	if (all->flags[i].d_greater_than)
	{
		if (*fd != -2)
			close(*fd);
		*fd = open(tmp_str, O_CREAT | O_RDWR | O_APPEND, 0777);
		all->arg[i].fd[1] = *fd;
	}
	if (all->flags[i].less_than)
	{
		if (*fd != -2)
			close(*fd);
		*fd = open(tmp_str, O_CREAT | O_RDWR, 0777);
		all->arg[i].fd[0] = *fd;
	}
	if (*fd == -1)
		return (0);
	return (1);
}

int	work_with_fd(t_all *all, int i)
{
	char	*tmp_str;
	int		tmp[2];
	int		fd;

	fd = -2;
	if (i < all->count)
		tmp_str = put_name_file(all->arg[i + 1].arguments[0]);
	if (all->flags[i].pipe)
	{
		pipe(tmp);
		all->arg[i].fd[1] = tmp[1];
		all->arg[i + 1].fd[0] = tmp[0];
	}
	if (do_if_greater_less(all, &fd, tmp_str, i) == 0)
		return (0);
	if (i < all->count)
		free(tmp_str);
	return (1);
}
