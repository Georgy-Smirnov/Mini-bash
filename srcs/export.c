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
	all->var.name_var = ft_strdup("");
	all->var.value_var = ft_strdup("");
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
	// printf("var.name_var: %s\n", all->var.name_var);
	// printf("var.value_var: %s\n", all->var.value_var);
}

int check_content(char *content, t_all *all)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	// printf("content: %s\n", content);
	// printf("var.name_var: %s\n", all->var.name_var);
	while(all->var.name_var[i] != '\0')
	{
		if (content[i] == all->var.name_var[i])
			return(1);
		i++;
	}
	return(0);
}

void	add_export(t_list *list, t_all *all)
{
	int		flag;
	t_list	*copy;
	// t_list	*tmp;

	flag = 0;
	copy = list;
	get_variable(all);
	while (copy != NULL)
	{
		// printf("1\n");
		// printf("content: %s\n", list->content);
		if (check_content(copy->content, all))
		{
			printf("arguments1: %s\n", all->arg->arguments[all->i + 1]);
			copy->content = ft_strdup(all->arg->arguments[all->i + 1]);
			list = copy;
			flag = 0;
			break;
		}
		else
			flag = 1;
		copy = copy->next;
	}
	printf("flag: %d\n", flag);
	if (flag)
	{
		printf("arguments: %s\n", all->arg->arguments[all->i + 1]);
		ft_lstadd_back(&list, ft_lstnew(ft_strdup(all->arg->arguments[all->i + 1])));
		// tmp = ft_lstnew(all->arg->arguments[all->i + 1]);
		// printf("content: %s\n", tmp->content);
		// printf("arguments: %s\n", all->arg->arguments[all->i + 1]);
	}
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

void		unset(t_list *list, t_all *all)
{
	t_list	*copy;
	// t_list	*after;

	copy = list;
	while (copy != NULL)
	{
		// printf("content: %s\n", copy->content);
		// printf("arguments1: %s\n", all->arg->arguments[all->i + 1]);
		// printf("ft_strncmp: %d", ft_strncmp(copy->content, all->arg->arguments[all->i + 1], ft_strlen(all->arg->arguments[all->i + 1])) == 0);
		
		// after = copy->next;
		if (ft_strncmp(copy->content, all->arg->arguments[all->i + 1], \
			ft_strlen(all->arg->arguments[all->i + 1])) == 0)
		{

			printf("content: %s\n", copy->content);
			copy = copy->next; 
			free(copy->next);
			copy->content = NULL;
			free(list->content);
			
			// list = copy;
			// free(copy);
			// free(copy);
			break;
		}
		copy = copy->next;
	}
	// free(copy);
	// output_list(copy);
}

void	parse_command(t_all *all, t_list *list)
{
	int i;

	all->i = 0;
	// printf("unset: %d", all->com[all->i].unset);
	while (all->i <= all->count)
	{
		if (all->com[all->i].exp)
			sort_export(list);
		else if (all->com[all->i].exp_add)
			add_export(list, all);
		else if (all->com[all->i].env)
			output_list(list);
		else if (all->com[all->i].unset)
			unset(list, all);
		else if (all->com[all->i].pwd)
			get_pwd(all);
		else if (all->com[all->i].cd)
			chdir(all->arg->arguments[all->i + 1]);
		else if (all->com[all->i].exit)
			get_exit(all);
		all->i++;
	}
}