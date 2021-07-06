#include "../../includes/minishell.h"

void	parse_command(t_all *all, t_list *list)
{
	int i;

	i = 0;
	all->i = 1;
	while (i <= all->count)
	{
		if (all->com[i].exp)
			sort_export(list, all, i);
		else if (all->com[i].exp_add)
			add_export(list, all);
		else if (all->com[i].env)
			output_list(list, all, i);
		else if (all->com[i].echo)
			ft_echo(all, i);
		else if (all->com[i].unset)
			unset(list, all);
		else if (all->com[i].pwd)
			get_pwd(all, i);
		else if (all->com[i].cd)
			chdir(all->arg->arguments[i + 1]);
		else if (all->com[i].exit)
			get_exit(all);
		else if (all->com[i].another)
			another_com(all, i);
		else
		{
			write(1, "minishell: ", 11);
			write(1, all->arg[i].arguments[0], ft_strlen(all->arg[i].arguments[0]));
			write(1, ": command not found\n", 20);
		}
		if (all->flags[i].less_than == 1 || all->flags[i].greater_than == 1 || all->flags[i].d_greater_than == 1)
			i += 2;
		else
			i++;
	}
}