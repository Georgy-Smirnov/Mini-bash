#include "minishell.h"

int	our_func(char *str)
{
	if (ft_strcmp(str, "export") == 0)
		return (1);
	if (ft_strcmp(str, "unset") == 0)
		return (1);
	if (ft_strcmp(str, "env") == 0)
		return (1);
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	if (ft_strcmp(str, "pwd") == 0)
		return (1);
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	return (0);
}

char	**search_in_env(t_list *list)
{
	char	*rez;
	char	**path;

	rez = NULL;
	while (list->next)
	{
		if (strncmp(list->content, "PATH=", 5) == 0)
		{
			rez = strdup(&list->content[5]);
			if (rez == NULL)
				return (NULL);
		}
		list = list->next;
	}
	path = ft_split(rez, ':');
	if (path == NULL)
		return (NULL);
	free(rez);
	return (path);
}

char	*surch_path(t_list *list, char *str)
{
	int			i;
	char		**path;
	struct stat	statbuf;

	i = 0;
	path = search_in_env(list);
	if (path == NULL)
		return (NULL);
	while (path[i])
	{
		path[i] = add_one_symbol_in_end(path[i], '/');
		path[i] = ft_strjoin_with_frees1(path[i], str);
		if (path[i] == NULL)
			return (NULL);
		if (stat(path[i], &statbuf) == 0)
			return (ft_strdup(path[i]));
		free(path[i]);
		i++;
	}
	free(path);
	return (NULL);
}

char	*change_one_arg(char *one_arg, t_all *all, t_list *list)
{
	char	*tmp;

	if (!our_func(one_arg))
	{
		tmp = surch_path(list, one_arg);
		if (tmp != NULL && ARG == NULL)
		{
			free(one_arg);
			one_arg = tmp;
			all->com[all->count].another = 1;
		}
	}
	return (one_arg);
}
