#include "../../includes/minishell.h"

void	get_variable(t_all *all)
{
	int	i;
	int	j;
	int	k;
	int	equally;

	i = 0;
	j = 0;
	k = 0;
	equally = 1;
	all->var.name_var = ft_strdup("");
	all->var.value_var = ft_strdup("");
	while (all->arg->arguments[all->i][j] != '\0')
	{
		if (all->arg->arguments[all->i][j] == '=' && equally)
		{
			equally = 0;
			// printf("equal1\n");
		}
		// printf("equal %d\n", equally);
		if (equally)
		{
			// printf("equal2\n");
			all->var.name_var[i] = all->arg->arguments[all->i][j];
		}
		else
		{
			all->var.value_var[k] = all->arg->arguments[all->i][j];
			k++;
		}
		i++;
		j++;
	}
	// printf("name_var %s\n", all->var.name_var);
	// printf("value_var %s\n", all->var.value_var);
}

void	free_get_variable(t_all *all)
{
	free(all->var.name_var);
	free(all->var.value_var);
}

void	add_export(t_list *list, t_all *all)
{
	t_list	*copy;

	all->nor.flag = 1;
	while (all->arg->arguments[all->i] != NULL)
	{
		get_variable(all);
		copy = list;
		while (copy != NULL)
		{
			if (!(ft_strncmp(copy->content, all->var.name_var, \
			ft_strlen(all->var.name_var))))
			{
				// printf("qqq\n");
				copy->content = ft_strdup(all->arg->arguments[all->i]);
				list = copy;
				all->nor.flag = 0;
				break ;
			}
			copy = copy->next;
		}
		if (all->nor.flag)
			ft_lstadd_back(&list, \
			ft_lstnew(ft_strdup(all->arg->arguments[all->i])));
		all->i++;
		free_get_variable(all);
	}
}
