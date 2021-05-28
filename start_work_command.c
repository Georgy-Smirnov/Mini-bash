#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return(0);
}

int	check_first_str(char *str, t_all *all)
{
	while (*str == ' ')
		str++;
	if (!ft_strncmp(str, "export", 6))
	{
		str+=6;
		while (*str == ' ')
			str++;
		if (ft_strlen(str) == 0)
			all->com.exp = 1;
		else
		{
			all->com.exp_add = 1;
			all->arg.str = str;
		}
		return(1);
	}
	else if (!ft_strncmp(str, "env", 3))
	{
		all->com.env = 1;
	}
	else if (!ft_strncmp(str, "unset", 3))
	{
		all->com.unset = 1;
	}
	return(0);	
}

void	bzero_t_all(t_all *all)
{
	all->com.exp = 0;
	all->com.exp_add = 0;
	all->arg.str = NULL;
	all->com.unset = 0;
	all->com.env = 0;
}

int	start_work_command(char *str, char **env)
{
	int i = 0;
	char **array;
	t_all *all;

	all = (t_all *)malloc(sizeof(t_all));
	if (all == NULL)
		return (0);
	bzero_t_all(all);
	array = ft_split(str, ';');
	int count = count_str_in_array(array);
	while (array[i])
	{
		check_first_str(array[i], all);
		i++;
	}
	printf(">>>exp = %d\n", all->com.exp);
	printf(">>>exp_add = %d\n", all->com.exp_add);
	printf(">>>str = %s\n", all->arg.str);
	printf(">>>unset = %d\n", all->com.unset);
	printf(">>>env = %d\n", all->com.env);
	parse_command(array, all, env);
	return (1);
}