#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <termios.h>
# include <term.h>
# include <termcap.h>
# include <curses.h>
# include <string.h>
# include "libft.h"

int		start_minishell(struct termios term, char **env);
void	print_d_array(char **hystory);
int	start_work_command(char *str, char **env);
int	ft_strcmp(char *s1, char *s2);
int	count_str_in_array(char **hystory);

typedef struct		s_arg
{
	char			*str;
}					t_arg;

typedef struct		s_command
{
	short int		exp;
	short int		exp_add; // ели ноль, то просто вывод отсортированного енв, если 1, значит добавить в енв
	short int		unset;
	short int		env;
	short int		echo;	//флаг echo
	short int		n;		//флаг -n для echo
	short int		cd;
	short int		pwd;
	short int		exit;
	short int		another; // другая команда, поиск бинарника
}					t_command;

typedef struct		s_all
{
	t_command		com;
	t_arg			arg;
}					t_all;

typedef struct		s_hystory
{
		char **array;
		int	count;
}					t_hystory;


#endif
