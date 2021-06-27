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
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

# include "../libft/libft.h"

typedef struct		s_variable
{
	char			*name_var;
	char			*value_var;
}					t_variable;

typedef struct		s_arg
{
	char			**arguments;
	int				*fd;
}					t_arg;

typedef struct		s_flags
{
	short int		pipe;
	short int		less_than;
	short int		greater_than;
	short int		d_greater_than;
}					t_flags;

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
	int				i;
	int				count;
	t_command		*com;
	t_arg			*arg;
	t_flags			*flags;
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
int		add_if_dollar(char *str, int *i, t_list *list, char **one_arg);
char	*add_one_symbol_in_end(char *str, char c);

void	parse_command(t_all *all, t_list *list);
t_list	*create_list(char **envp);
void	output_list(t_list *list);
void	get_pwd(t_all *all);
void    get_exit(t_all *all);
char	*put_end_of_string();
char	*add_one_symbol_in_end(char *str, char c);

t_all	*create_struct(void);
int		add_in_struct(t_all *all);
void	clean_struct(t_all *all);

void	print_struct(t_all *all);
int	skip_space(char *str, int i);
int	check_errors(char *str);


void	check_build_in_command(t_all *all);

#endif
