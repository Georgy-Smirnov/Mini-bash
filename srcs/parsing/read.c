#include "../../includes/minishell.h"

void	check_buf(char *buf, char **rez, t_hystory *hys)
{
	if (!strcmp(buf, "\177"))
		*rez = do_if_backspace(*rez);
	else if (!(strcmp(buf, "\e[A")))
		*rez = do_if_up(*rez, hys);
	else if (!(strcmp(buf, "\e[B")))
		*rez = do_if_down(*rez, hys);
	else if (!(strcmp(buf, "\e[C")) || !(strcmp(buf, "\e[D")))
		rez = rez;
	else
	{
		write (1, buf, 1);
		if (*buf != '\n')
			*rez = ft_strjoin_with_frees1(*rez, buf);
	}
}

int	read_end_of_str(char **rez, t_hystory *hys)
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
		check_buf(buf, rez, hys);
		if (rez == NULL)
			return (-5);
		if (*buf == '\n' || strcmp(buf, "\4") == 0)
			break ;
	}
	free(buf);
	return (strcmp(buf, "\4"));
}

int	main_cycle(char **rez, t_hystory *hys, char **env)
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
		buf = read_end_of_str(rez, hys);
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

int	start_minishell(char **env)
{
	char		*rez;
	t_hystory	hystory;

	rez = put_end_of_string();
	if (rez == NULL)
		return (0);
	hystory.array = NULL;
	if (main_cycle(&rez, &hystory, env) == 0)
		return (0);
	return (1);
}
