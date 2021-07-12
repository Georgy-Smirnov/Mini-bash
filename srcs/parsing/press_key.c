#include "minishell.h"

char	*do_if_backspace(char *rez)
{
	if (ft_strlen(rez) > 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		rez = ft_dellastchar(rez);
	}
	return (rez);
}

char	*do_if_up(char *rez, t_hystory *hystory)
{
	if (hystory->count > 0)
	{
		hystory->count--;
		free(rez);
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar);
		ft_putstr_fd(hystory->array[hystory->count], 1);
		rez = ft_strdup(hystory->array[hystory->count]);
		if (rez == NULL)
			return (NULL);
	}
	return (rez);
}

char	*do_if_down(char *rez, t_hystory *hystory)
{
	if (hystory->count < count_str_in_array(hystory->array) - 1)
	{
		hystory->count++;
		free(rez);
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar);
		ft_putstr_fd(hystory->array[hystory->count], 1);
		rez = ft_strdup(hystory->array[hystory->count]);
		if (rez == NULL)
			return (0);
	}
	else if (hystory->count == count_str_in_array(hystory->array) - 1)
	{
		hystory->count++;
		free(rez);
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar);
		rez = (char *)malloc(sizeof(char));
		if (rez == NULL)
			return (0);
		*rez = 0;
	}
	return (rez);
}
