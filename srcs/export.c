#include "../includes/minishell.h"

void	output_list(t_list *list)
{
	while (list->next != NULL)
	{
		list = list->next;
		printf("%s\n", list->content);
	}
}

t_list	*create_list(char **envp)
{
	int i;
	t_list *list;

	list = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		ft_lstadd_back(&list, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	return(list);
}

void	get_variable(t_all *all)
{
	int	i;
	int j;
	int k;
	int	equally;

	i = 0;
	j = 0;
	k = 0;
	equally = 0;
	while (all->arg->arguments[all->i + 1][j] != '\0')
	{
		if (all->arg->arguments[all->i + 1][j] == '=')
			equally = 1;
		if (!equally)
			all->var.name_var[i] = all->arg->arguments[all->i + 1][j];
		else
		{
			all->var.value_var[k] = all->arg->arguments[all->i + 1][j];
			k++;
		}
		i++;
		j++;
	}
}

int check_content(char *content, t_all *all)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while(all->var.name_var[i] != '\0')
	{
		if (content[i] == all->var.name_var[i])
			return(1);
		i++;
	}
	return(0);
	// return(1);
}

void	add_export(t_list *list, t_all *all)
{
	int		flag;
	t_list	*copy_list;

	flag = 0;
	copy_list = list;
	all->var.name_var = ft_strdup("");
	all->var.value_var = ft_strdup("");
	get_variable(all);
	while (copy_list != NULL)
	{
		if (check_content(copy_list->content, all))
		{
			copy_list->content = all->arg->arguments[all->i + 1];
			flag = 0;
			break;
		}
		else
			flag = 1;
		copy_list = copy_list->next;
	}
	if (flag)
		ft_lstadd_back(&list, ft_lstnew(all->arg->arguments[all->i + 1]));
	// output_list(list);
}

void	output_export(t_list *list)
{
	t_list *copy;
	char *str;
	int i;

	copy = list->next;
	i = 0;
	while (copy != NULL)
	{
		str = (char *)(copy->content);
		ft_putstr_fd("declare -x ", 1);
		while (str[i] != '=' && str[i])
			write(1, &str[i++], 1);
		if (str[i] == '=')
			write(1, &str[i++], 1);
		write(1, "\"", 1);
		while (str[i])
			write(1, &str[i++], 1);
		write(1, "\"", 1);
		write(1, "\n", 1);
		copy = copy->next;
		i = 0;
	}
}

void	sort_export(t_list *list)
{
	t_list *copy;
	t_list *next;
	char *str1;
	char *str2;
	char *tmp;

	copy = list->next;
	next = list->next->next;
	while (copy->next != NULL)
	{
		while (next->next != NULL)
		{
			str1 = (char *)(copy->content);
			str2 = (char *)(next->content);
			if (ft_strcmp(str1, str2) > 0)
			{
				tmp = str1;
				copy->content = str2;
				next->content = tmp;
			}
			next = next->next;
		}
		copy = copy->next;
		next = copy;
	}
	output_export(list);
}

// void		unset(char *name_varible, t_all *all, t_list *list)
// {
// 	char	*str_env;
// 	t_list	*copy_list;

// 	copy_list = list;
// 	while (copy_list->next != NULL)
// 	{
// 		if (ft_strcmp(copy_list->content, name_varible) == 0)
// 		{
// 			free(copy_list->content);
// 			break;
// 		}
// 		copy_list = copy_list->next;
// 	}
// 	output_list(copy_list);
// }

void	parse_command(t_all *all, t_list *list)
{
	int i;

	all->i = 0;
	while (all->i <= all->count)
	{
		// printf("!!!QQQ!!!\n");
		if (all->com[all->i].exp)
			sort_export(list);
		else if (all->com[all->i].exp_add)
			add_export(list, all);
		else if (all->com[all->i].env)
			output_list(list);
		all->i++;
	}
}