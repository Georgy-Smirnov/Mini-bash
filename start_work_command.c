#include "minishell.h"


void	print_struct(t_all *all)
{
	printf(">>>exp = %d\n", all->com.exp);
	printf(">>>exp_add = %d\n", all->com.exp_add);
	printf(">>>str = %s\n", all->arg.str);
	printf(">>>unset = %d\n", all->com.unset);
	printf(">>>env = %d\n", all->com.env);
	printf("************\n");
	print_d_array(all->arg.arguments);
}


int	start_work_command(t_all *all, t_list *list)
{
	// parse_command(all, list);
	print_struct(all);
	return (1);
}