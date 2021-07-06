#include "../../includes/minishell.h"

t_list	*create_list(char **envp)
{
	int		i;
	t_list	*list;

	list = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		ft_lstadd_back(&list, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	return (list);
}
