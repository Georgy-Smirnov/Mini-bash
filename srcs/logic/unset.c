#include "../../includes/minishell.h"

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
			if (ft_strlen(var) == i && (str[i] == '=' || ft_strchr(var, '=') == 0))
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