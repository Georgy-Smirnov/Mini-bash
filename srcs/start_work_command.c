#include "../includes/minishell.h"


void	print_struct(t_all *all)
{
	int i = 0;

	printf("*******************************\n");
	printf("count: %d\n", all->count);
	printf("*******************************\n\n\n");
	while (i <= all->count)
	{
		printf("*******************************\n");
		printf("***********struct %d************\n", i);
		printf("*******************************\n");
		printf("exp: %d\n", all->com[i].exp);
		printf("exp_add: %d\n", all->com[i].exp_add);
		printf("unset: %d\n", all->com[i].unset);
		printf("env: %d\n", all->com[i].env);
		printf("echo: %d\n", all->com[i].echo);
		printf("n: %d\n", all->com[i].n);
		printf("cd: %d\n", all->com[i].cd);
		printf("pwd: %d\n", all->com[i].pwd);
		printf("exit: %d\n", all->com[i].exit);
		printf("another: %d\n", all->com[i].another);
		printf("*******************************\n");
		printf("pipe: %d\n", all->flags[i].pipe);
		printf("less_than: %d\n", all->flags[i].less_than);
		printf("greater_than: %d\n", all->flags[i].greater_than);
		printf("d_greater_than: %d\n", all->flags[i].d_greater_than);
		printf("*******************************\n");
		print_d_array(all->arg[i].arguments);
		i++;
	}
}

void	check_build_in_command(t_all *all)
{
	if (!ft_strncmp(all->arg[all->count].arguments[0], "export", 6) && all->arg[all->count].arguments[1] == NULL)
		all->com[all->count].exp = 1;
	else if (!ft_strncmp(all->arg[all->count].arguments[0], "export", 6))
	{
		all->com[all->count].exp = 0;
		all->com[all->count].exp_add = 1;
	}
	else if (!ft_strncmp(all->arg[all->count].arguments[0], "unset", 5))
		all->com[all->count].unset = 1;
	else if (!ft_strncmp(all->arg[all->count].arguments[0], "env", 3))
		all->com[all->count].env = 1;
	else if (!ft_strncmp(all->arg[all->count].arguments[0], "cd", 2))
		all->com[all->count].cd = 2;
	else if (!ft_strncmp(all->arg[all->count].arguments[0], "pwd", 3))
		all->com[all->count].pwd = 1;
	else if (!ft_strncmp(all->arg[all->count].arguments[0], "exit", 4))
		all->com[all->count].exit = 1;
	else if (!ft_strncmp(all->arg[all->count].arguments[0], "echo", 4))
	{
		all->com[all->count].echo = 1;
		if (all->arg[all->count].arguments[1] != NULL && !ft_strncmp(all->arg[all->count].arguments[1], "-n", 2))
			all->com[all->count].n = 1;
	}
}

int	start_work_command(t_all *all, t_list *list)
{
	parse_command(all, list);
	print_struct(all);
	return (1);
}