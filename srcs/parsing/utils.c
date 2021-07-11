#include "../../includes/minishell.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int	count_str_in_array(char **hystory)
{
	int	i;

	i = 0;
	if (hystory == NULL)
		return (0);
	while (hystory[i] != NULL)
		i++;
	return (i);
}

char	**create_array(char *str)
{
	char	**rez;

	rez = (char **)malloc(sizeof(char *) * 2);
	if (rez == NULL)
		return (NULL);
	rez[0] = ft_strdup(str);
	rez[1] = NULL;
	return (rez);
}

char	**add_in_array(char **hystory, char *str)
{
	char	**rez;
	int		count;
	int		i;

	i = 0;
	if (hystory == NULL)
		rez = create_array(str);
	else
	{
		count = count_str_in_array(hystory);
		rez = (char **)malloc(sizeof(char *) * (count + 2));
		if (rez == NULL)
			return (NULL);
		while (i < count)
		{
			rez[i] = hystory[i];
			i++;
		}
		rez[i] = ft_strdup(str);
		rez[i + 1] = NULL;
		free(hystory);
	}
	return (rez);
}

char	*put_end_string(void)
{
	char	*rez;

	rez = (char *)malloc(sizeof(char));
	if (rez == NULL)
		return (NULL);
	*rez = 0;
	return (rez);
}
