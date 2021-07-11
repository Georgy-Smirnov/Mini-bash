#include "../../includes/minishell.h"

char	*do_if_backspace(struct termios term, char *rez)
{
	if (ft_strlen(rez) > 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		rez = ft_dellastchar(rez);
	}
	return (rez);
}

char	*do_if_up(struct termios term, char *rez, t_hystory *hystory)
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

char	*do_if_down(struct termios term, char *rez, t_hystory *hystory)
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

void	check_buf(char *buf, char **rez, t_hystory *hys, struct termios term)
{
	if (!strcmp(buf, "\177"))
		*rez = do_if_backspace(term, *rez);
	else if (!(strcmp(buf, "\e[A")))
		*rez = do_if_up(term, *rez, hys);
	else if (!(strcmp(buf, "\e[B")))
		*rez = do_if_down(term, *rez, hys);
	else if (!(strcmp(buf, "\e[C")) || !(strcmp(buf, "\e[D")))
		rez = rez;
	else
	{
		write (1, buf, 1);
		if (*buf != '\n')
			*rez = ft_strjoin_with_frees1(*rez, buf);
	}
}

int	read_end_of_str(char **rez, t_hystory *hys, struct termios term)
{
	char	*buf;
	int		rs;

	buf = (char *)malloc(sizeof(char) * 5);
	if (buf == NULL)
		return (-5);
	while (TRUE)
	{
		rs = read(0, buf, 5);
		if (rs == -1)
			return (-5);
		buf[rs] = 0;
		check_buf(buf, rez, hys, term);
		if (rez == NULL)
			return (-5);
		if (*buf == '\n' || strcmp(buf, "\4") == 0)
			break ;
	}
	free(buf);
	return (strcmp(buf, "\4"));
}

int	main_cycle(char **rez, struct termios term, t_hystory *hys, char **env)
{
	int		buf;
	t_list	*list;

	buf = 1;
	list = create_list(env);
	while (buf != 0)
	{
		write (1, "\e[1;32mMinishell% \e[0m", 22);
		**rez = 0;
		tputs(save_cursor, 1, ft_putchar);
		hys->count = count_str_in_array(hys->array);
		buf = read_end_of_str(rez, hys, term);
		if (buf == -5)
			return (0);
		if (buf == 0)
			break ;
		hys->array = add_in_array(hys->array, *rez);
		if (hys->array == NULL)
			return (0);
		if (start_parse_command(*rez, list) == 0)
			return (0);
	}
	return (1);
}

int	start_minishell(struct termios term, char **env)
{
	char		*rez;
	t_hystory	hystory;

	rez = put_end_string();
	if (rez == NULL)
		return (0);
	hystory.array = NULL;
	if (main_cycle(&rez, term, &hystory, env) == 0)
		return (0);
	return (1);
}
