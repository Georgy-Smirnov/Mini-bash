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

int	start_minishell(struct termios term)
{
	char buf[3];
	int rs;
	int count;
	char **hystory;
	char *rez;

	rez = put_end_string();
	if (rez == NULL)
		return (0);
	hystory = NULL;
	while (strcmp(buf, "\4"))
	{
		write (1, "Minishell% ", 11);
		*rez = 0;
		tputs(save_cursor, 1, ft_putchar);
		count = count_str_in_array(hystory);
		while (TRUE)
		{
			rs = read (0, buf, 3);
			if (rs == -1)
			{
				write (1, "3Error!", 6);
				return(0);
			}
			buf[rs] = 0;
			if (!strcmp(buf, "\177"))
				rez = do_if_backspace(term, rez);
			else if (!(strcmp(buf, "\e[A")))
			{
				if (count > 0)
				{
					count--;
					free(rez);
					tputs(restore_cursor, 1, ft_putchar);
					tputs(tgetstr("ce", 0), 1, ft_putchar);
					ft_putstr_fd(hystory[count], 1);
					rez = ft_strdup(hystory[count]);
					if (rez == NULL)
						return (0);
				}
			}
			else if (!(strcmp(buf, "\e[B")))
			{
				if (count < count_str_in_array(hystory) - 1)
				{
					count++;
					free(rez);
					tputs(restore_cursor, 1, ft_putchar);
					tputs(tgetstr("ce", 0), 1, ft_putchar);
					ft_putstr_fd(hystory[count], 1);
					rez = ft_strdup(hystory[count]);
					if (rez == NULL)
						return (0);
				}
				else if (count == count_str_in_array(hystory) - 1)
				{
					count++;
					free(rez);
					tputs(restore_cursor, 1, ft_putchar);
					tputs(tgetstr("ce", 0), 1, ft_putchar);
					rez = (char *)malloc(sizeof(char));
					if (rez == NULL)
						return (0);
					*rez = 0;
				}
			}
			else if (!(strcmp(buf, "\e[C")) || !(strcmp(buf, "\e[D")))
			{	
			}
			else
			{
				write (1, buf, rs);
				if (*buf != '\n')
					rez = ft_strjoin_with_frees1(rez, buf);

			}	
			if (*buf == '\n' || strcmp(buf, "\4") == 0)
				break;
		}
		if (strcmp(buf, "\4") == 0)
			break;
		hystory = add_in_array(hystory, rez);
		if (hystory == NULL)
			return (0);
		if (start_work_command(rez) == 0)
			return (0);
	}
	printf("HYSTORY:\n");
	print_d_array(hystory);
	return (1);
}