#include "minishell.h"

int ft_putchar(int c)
{
	return(write(1, &c, 1));
}

int	count_str_in_array(char **hystory)
{
	int i;

	i = 0;
	if (hystory == NULL)
		return (0);
	while (hystory[i] != NULL)
		i++;
	return (i);
}

void	print_d_array(char **hystory)
{
	int i;

	i = 0;
	if (hystory == NULL)
		ft_putstr_fd("null", 1);
	else
	{
		while (hystory[i] != NULL)
		{
			ft_putstr_fd(hystory[i], 1);
			i++;
			write(1, "\n", 1);
		}
	}
}

void print_hystory(char **hystory, int q)
{
	ft_putstr_fd(hystory[q], 1);
}



char **add_in_array(char **hystory, char *str)
{
	char **rez;
	int count;
	int i;

	i = 0;
	if (hystory == NULL)
	{
		rez = (char **)malloc(sizeof(char *) * 2);
		if (rez == NULL)
			return (NULL);
		*rez = ft_strdup(str);
		rez[1] = NULL;
	}
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

char *put_end_string()
{
	char *rez;

	rez = (char *)malloc(sizeof(char));
	if  (rez == NULL)
		return (NULL);
	*rez = 0;
	return (rez);
}

char *do_if_backspace(struct termios term, char *rez)
{
	if (ft_strlen(rez) > 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		rez = ft_dellastchar(rez);
	}
	return (rez);
}

char *do_if_up(struct termios term, char *rez, t_hystory *hystory)
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

char *do_if_down(struct termios term, char *rez, t_hystory *hystory)
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

int		read_before_end_of_string(char **rez, t_hystory *hystory, struct termios term)
{
	char buf[5];
	int rs;

	while (TRUE)
	{
		rs = read(0, buf, 5);
		if (rs == -1)
		{
			write (1, "Read error!", 6);
			return(-5);
		}
		buf[rs] = 0;
		if (!strcmp(buf, "\177"))
			*rez = do_if_backspace(term, *rez);
		else if (!(strcmp(buf, "\e[A")))
			*rez = do_if_up(term, *rez, hystory);
		else if (!(strcmp(buf, "\e[B")))
			*rez = do_if_down(term, *rez, hystory);
		else if (!(strcmp(buf, "\e[C")) || !(strcmp(buf, "\e[D")))
			rez = rez;
		else
		{
			write (1, buf, rs);
			if (*buf != '\n')
				*rez = ft_strjoin_with_frees1(*rez, buf);
		}
		if (rez == NULL)
			return (-5);
			//НЕ ВЫДЕЛИЛАСЬ ПАМЯТЬ
		if (*buf == '\n' || strcmp(buf, "\4") == 0)
			break;
	}
	return (strcmp(buf, "\4"));
}

int	do_in_main_cycle(char **rez, struct termios term, t_hystory *hystory, char **env)
{
	int buf;

	buf = 1;
	while (buf != 0)
	{
		write (1, "\e[1;32mMinishell% \e[0m", 22);
		**rez = 0;
		tputs(save_cursor, 1, ft_putchar);
		hystory->count = count_str_in_array(hystory->array);
		buf = read_before_end_of_string(rez, hystory, term); // Если buf == -5, то ошибка в чтении строки, если == 0 то Ctrl+D
		if (buf == -5)
			return (0);
		if (buf == 0)
			break;
		hystory->array = add_in_array(hystory->array, *rez);
		if (hystory->array == NULL)
			return (0);
		if (start_work_command(*rez, env) == 0)
			return (0);
	}
	return (1);
}

int	start_minishell(struct termios term, char **env)
{
	char *rez; //перенести объявление в функцию с мейн-циклом
	t_hystory hystory;

	rez = put_end_string();
	if (rez == NULL)
		return (0);
	hystory.array = NULL;
	if (do_in_main_cycle(&rez, term, &hystory, env) == 0)
		return (0);
	printf("HYSTORY:\n");
	print_d_array(hystory.array);
	return (1);
}