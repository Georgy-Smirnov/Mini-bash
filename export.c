// #include "minishell.h"

// void	output_list(t_list *list)
// {
// 	while (list->next != NULL)
// 	{
// 		list = list->next;
// 		printf("%s\n", list->content);
// 	}
// }

// t_list	*create_list(char **envp)
// {
// 	int i;
// 	t_list *list;

// 	i = 0;
// 	while (envp[i] != NULL)
// 	{
// 		ft_lstadd_back(&list, ft_lstnew(ft_strdup(envp[i])));
// 		i++;
// 	}
// 	return(list);
// }

// void	add_export(char *name_varible, char *value_varible, t_list *list)
// {
// 	char	*str_env;
// 	int		flag;
// 	t_list	*copy_list;

// 	copy_list = list;
// 	str_env = ft_strjoin(name_varible, value_varible);
// 	while (copy_list->next != NULL)
// 	{
// 		if (ft_strcmp(copy_list->content, name_varible) == 0)
// 		{
// 			copy_list->content = str_env;
// 			flag = 0;
// 			break;
// 		}
// 		else
// 			flag = 1;
// 		copy_list = copy_list->next;
// 	}
// 	if (flag)
// 		ft_lstadd_back(&list, ft_lstnew(str_env));
// 	output_list(list);
// }

// void	output_export(t_list *list)
// {
// 	t_list *copy;
// 	char *str;
// 	int i;

// 	copy = list->next;
// 	i = 0;
// 	while (copy != NULL)
// 	{
// 		str = (char *)(copy->content);
// 		ft_putstr_fd("declare -x ", 1);
// 		while (str[i] != '=' && str[i])
// 			write(1, &str[i++], 1);
// 		if (str[i] == '=')
// 			write(1, &str[i++], 1);
// 		write(1, "\"", 1);
// 		while (str[i])
// 			write(1, &str[i++], 1);
// 		write(1, "\"", 1);
// 		write(1, "\n", 1);
// 		copy = copy->next;
// 		i = 0;
// 	}
// }

// void	sort_export(t_list *list)
// {
// 	t_list *copy;
// 	t_list *next;
// 	char *str1;
// 	char *str2;
// 	char *tmp;

// 	copy = list->next;
// 	next = list->next->next;
// 	while (copy->next != NULL)
// 	{
// 		while (next->next != NULL)
// 		{
// 			str1 = (char *)(copy->content);
// 			str2 = (char *)(next->content);
// 			if (ft_strcmp(str1, str2) > 0)
// 			{
// 				tmp = str1;
// 				copy->content = str2;
// 				next->content = tmp;
// 			}
// 			next = next->next;
// 		}
// 		copy = copy->next;
// 		next = copy;
// 	}
// 	output_export(list);
// }

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

// void		manage_export(char *name_varible, char *value_varible, char **envp, t_all *all)
// {
// 	int		temp_flag;
// 	t_list	*list;

// 	list = create_list(envp);
// 	temp_flag = 2;
// 	if (temp_flag == 1)
// 		add_export(name_varible, value_varible, list);
// 	else if (temp_flag == 2)
// 		sort_export(list);
// 	// else if (temp_flag == 2)
// 	// 	printf("!!!QQQ!!!\n");
// 		// unset(name_varible, all, list);
// }



// int			main(int argc, char **argv, char **envp)
// {
// 	char	*name_varible;
// 	char	*value_varible;
// 	t_all	*all;
	
// 	name_varible = ft_strdup("abc=");
// 	value_varible = ft_strdup("123");
// 	manage_export(name_varible, value_varible, envp, all);
	
// }