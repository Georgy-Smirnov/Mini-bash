#include "minishell.h"

t_command	*b_zero(t_command *tmp, int i)
{
	tmp[i].exp = 0;
	tmp[i].exp_add = 0;
	tmp[i].unset = 0;
	tmp[i].env = 0;
	tmp[i].echo = 0;
	tmp[i].n = 0;
	tmp[i].cd = 0;
	tmp[i].pwd = 0;
	tmp[i].exit = 0;
	tmp[i].another = 0;
	return (tmp);
}

int	add_in_com(t_all *all)
{
	int			i;
	t_command	*tmp;

	i = 0;
	tmp = (t_command *)malloc(sizeof(t_command) * (all->count + 1));
	if (tmp == NULL)
		return (0);
	while (i < all->count)
	{
		tmp[i].exp = all->com[i].exp;
		tmp[i].exp_add = all->com[i].exp_add;
		tmp[i].unset = all->com[i].unset;
		tmp[i].env = all->com[i].env;
		tmp[i].echo = all->com[i].echo;
		tmp[i].n = all->com[i].n;
		tmp[i].cd = all->com[i].cd;
		tmp[i].pwd = all->com[i].pwd;
		tmp[i].exit = all->com[i].exit;
		tmp[i].another = all->com[i].another;
		i++;
	}
	b_zero(tmp, i);
	free(all->com);
	all->com = tmp;
	return (1);
}

int	add_in_arg(t_all *all)
{
	int		i;
	t_arg	*tmp;

	i = 0;
	tmp = (t_arg *)malloc(sizeof(t_arg) * (all->count + 1));
	if (tmp == NULL)
		return (0);
	while (i < all->count)
	{
		tmp[i].arguments = all->arg[i].arguments;
		tmp[i].fd = all->arg[i].fd;
		i++;
	}
	tmp[i].arguments = NULL;
	tmp[i].fd = (int *)malloc(sizeof(int) * 2);
	if (tmp[i].fd == NULL)
		return (0);
	tmp[i].fd[0] = 0;
	tmp[i].fd[1] = 1;
	free(all->arg);
	all->arg = tmp;
	return (1);
}

int	add_in_flags(t_all *all)
{
	int		i;
	t_flags	*tmp;

	i = 0;
	tmp = (t_flags *)malloc(sizeof(t_flags) * (all->count + 1));
	if (tmp == NULL)
		return (0);
	while (i < all->count)
	{
		tmp[i].pipe = all->flags[i].pipe;
		tmp[i].less_than = all->flags[i].less_than;
		tmp[i].greater_than = all->flags[i].greater_than;
		tmp[i].d_greater_than = all->flags[i].d_greater_than;
		i++;
	}
	tmp[i].pipe = 0;
	tmp[i].less_than = 0;
	tmp[i].greater_than = 0;
	tmp[i].d_greater_than = 0;
	free(all->flags);
	all->flags = tmp;
	return (1);
}

int	add_in_struct(t_all *all)
{
	all->count++;
	if (add_in_com(all) && add_in_flags(all) && add_in_arg(all))
		return (1);
	else
		return (0);
}
