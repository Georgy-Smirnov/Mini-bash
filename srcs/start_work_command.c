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

int	start_work_command(t_all *all, t_list *list)
{
	// parse_command(all, list);
	print_struct(all);
	return (1);
}