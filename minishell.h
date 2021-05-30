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

typedef struct		s_variable
{
	char			*name_var;
	char			*value_var;
}					t_variable;

typedef struct		s_arg
{
	char			*str;
	char			**arguments;
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
	t_variable		var;
}					t_all;

typedef struct		s_hystory
{
		char **array;
		int	count;
}					t_hystory;

int		start_minishell(struct termios term, char **env);
int		start_parse_command(char *str, t_list *list);
int		start_work_command(t_all *all, t_list *list);

void	print_d_array(char **hystory);
int		ft_strcmp(char *s1, char *s2);
int		count_str_in_array(char **hystory);
char 	**add_in_array(char **hystory, char *str);

char	*add_if_one_quote(char *one_arg, char *str, int *i);
char	*add_if_two_quote(char *one_arg, char *str, int *i, t_list *list);
char	*add_if_dollar(char *str, int *i, t_list *list);
char	*add_one_symbol_in_end(char *str, char c);

void	parse_command(t_all *all, t_list *list);
t_list	*create_list(char **envp);
char	*put_end_of_string();
char	*add_one_symbol_in_end(char *str, char c);

#endif
