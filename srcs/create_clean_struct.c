#include "../includes/minishell.h"

void	zero_b(t_all *tmp)
{
	tmp->count = 0;
	tmp->arg[0].arguments = NULL;
	tmp->arg[0].fd[0] = 0;
	tmp->arg[0].fd[1] = 1;
	tmp->com[0].exp = 0;
	tmp->com[0].exp_add = 0;
	tmp->com[0].unset = 0;
	tmp->com[0].env = 0;
	tmp->com[0].echo = 0;
	tmp->com[0].n = 0;
	tmp->com[0].cd = 0;
	tmp->com[0].pwd = 0;
	tmp->com[0].exit = 0;
	tmp->com[0].another = 0;
	tmp->flags[0].pipe = 0;
	tmp->flags[0].less_than = 0;
	tmp->flags[0].greater_than = 0;
	tmp->flags[0].d_greater_than = 0;
}

t_all	*create_struct(void)
{
	t_all	*tmp;

	tmp = (t_all *)malloc(sizeof(t_all));
	if (tmp == NULL)
		return (NULL);
	tmp->arg = (t_arg *)malloc(sizeof(t_arg));
	if (tmp->arg == NULL)
		return (NULL);
	tmp->com = (t_command *)malloc(sizeof(t_command));
	if (tmp->com == NULL)
		return (NULL);
	tmp->flags = (t_flags *)malloc(sizeof(t_flags));
	if (tmp->flags == NULL)
		return (NULL);
	tmp->arg[0].fd = (int *)malloc(sizeof(int) * 2);
	if (tmp->arg[0].fd == NULL)
		return (NULL);
	zero_b(tmp);
	return (tmp);
}

void	clean_d_array(char **array)
{
	int	i;

	i = 0;
	if (array != NULL)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array[i]);
		free(array);
	}
}

void	clean_struct(t_all *all)
{
	int	i;

	i = 0;
	while (i <= all->count)
	{
		clean_d_array(all->arg[i].arguments);
		free(all->arg[i].fd);
		i++;
	}
	free(all->arg);
	free(all->com);
	free(all->flags);
	free(all);
}
