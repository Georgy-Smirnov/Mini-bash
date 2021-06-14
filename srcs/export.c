#include "../includes/minishell.h"

#define EXIST_VALUE 1
#define NOT_EXIST_VALUE 0

void	output_list(t_list *list)
{
	while (list->next != NULL)
	{
		list = list->next;
		if (ft_strchr(list->content, '='))
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
	while (all->arg->arguments[all->i][j] != '\0')
	{
		if (all->arg->arguments[all->i][j] == '=')
			equally = 1;
		if (!equally)
			all->var.name_var[i] = all->arg->arguments[all->i][j];
		else
		{
			all->var.value_var[k] = all->arg->arguments[all->i][j];
			k++;
		}
		i++;
		j++;
	}
}

void	add_export(t_list *list, t_all *all)
{
	int		flag;
	t_list	*copy;

	flag = 1;
	while (all->arg->arguments[all->i] != NULL)
	{
		get_variable(all);
		copy = list;
		while (copy != NULL)
		{
			if (!(ft_strncmp(copy->content, all->var.name_var, ft_strlen(all->var.name_var))))
			{
				copy->content = ft_strdup(all->arg->arguments[all->i]);
				list = copy;
				flag = 0;
				break;
			}
			copy = copy->next;
		}
		if (flag)
			ft_lstadd_back(&list, ft_lstnew(ft_strdup(all->arg->arguments[all->i])));
		all->i++;
		free(all->var.name_var);
		free(all->var.value_var);
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
		if (ft_strchr(copy->content, '='))
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
			i = 0;
		}
		else
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(copy->content, 1);
			write(1, "\n", 1);
		}
		copy = copy->next;
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

int				exist_value_env(t_list *list, char *value)
{
	t_list *copy;
	int i;
	char *str;

	copy = list;
	i = 0;
	while (copy->next != NULL)
	{
		copy = copy->next;
		str = (char *)copy->content;
		while (str[i] != '=' && str[i] && value[i])
		{
			if (str[i] == value[i])
				i++;
			else
				break ;
		}
		if (ft_strlen(value) == i)
			return (1);
		i = 0;
	}
	return (0);
}


//обработать удаление без =
void			unset(t_list *list, t_all *all)
{
	t_list *copy;
	t_list *before;
	t_list *after;
	int i;
	int j;
	int k;
	char *str;
	char *var;
	int boolean;

	copy = list;
	i = 0;
	j = 0;
	k = 0;
	get_variable(all);
	var = ft_strjoin(all->var.name_var, all->var.value_var);
	boolean = exist_value_env(list, var);
	if (boolean)
	{
		while (copy->next != NULL)
		{
			copy = copy->next;
			str = copy->content;
			while (str[i] == var[i] && str[i] != '\0' && var[i] != '\0')
				i++;
			if (ft_strlen(var) == i && str[i] == '=')
				break ;
			i = 0;
			j++;
		}
		after = copy->next;
		before = list->next;
		while (k != (j - 1))
		{
			before = before->next;
			k++;
		}
		free(copy);
		free(var);
		if (before->next != NULL)
			before->next = after;
	}
}

void	parse_command(t_all *all, t_list *list)
{
	int i;

	i = 0;
	all->i = 1;
	while (i <= all->count)
	{
		if (all->com[i].exp)
			sort_export(list);
		else if (all->com[i].exp_add)
			add_export(list, all);
		else if (all->com[i].env)
			output_list(list);
		else if (all->com[i].unset)
			unset(list, all);
		else if (all->com[i].pwd)
			get_pwd(all);
		else if (all->com[i].cd)
			chdir(all->arg->arguments[i + 1]);
		else if (all->com[i].exit)
			get_exit(all);
		i++;
	}
}