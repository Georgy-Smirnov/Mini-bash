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
# include <signal.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"

int	g_err;

typedef struct s_for_normy
{
	char			*str1;
	char			*str2;
	char			*tmp;
	char			flag;
	int				unset_i;
	int				unset_j;
	int				l;
}					t_for_normy;

typedef struct s_arg
{
	char			**arguments;
	int				*fd;
}					t_arg;

typedef struct s_flags
{
	short int		pipe;
	short int		less_than;
	short int		greater_than;
	short int		d_greater_than;
}					t_flags;

typedef struct s_command
{
	short int		exp;
	short int		exp_add;
	short int		unset;
	short int		env;
	short int		echo;
	short int		n;
	short int		cd;
	short int		pwd;
	short int		exit;
	short int		another;
}					t_command;

typedef struct s_all
{
	int				i;
	int				count;
	int				tmp_fd1;
	int				tmp_fd0;
	t_command		*com;
	t_arg			*arg;
	t_flags			*flags;
	t_for_normy		n;
}					t_all;

typedef struct s_hystory
{
	char	**array;
	int		count;
}					t_hystory;

int		start_minishell(char **env);
char	*do_if_backspace(char *rez);
char	*do_if_up(char *rez, t_hystory *hystory);
char	*do_if_down(char *rez, t_hystory *hystory);
int		ft_putchar(int c);
char	*put_end_of_string(void);
int		work_with_fd(t_all *all, int i, int *fd);
char	*put_variable(char *str, int *i, t_list *list);
char	*change_one_arg(char *one_arg, t_all *all, t_list *list);
int		write_one_arg(char **one_arg, char *str, int *i, t_list *list);
int		start_parse_command(char *str, t_list *list);
int		start_work_command(t_all *all, t_list *list);
void	print_d_array(char **hystory);
int		ft_strcmp(char *s1, char *s2);
int		count_str_in_array(char **hystory);
char	**add_in_array(char **hystory, char *str);
char	*add_if_one_quote(char *one_arg, char *str, int *i);
char	*add_if_two_quote(char *one_arg, char *str, int *i, t_list *list);
int		add_if_dollar(char *str, int *i, t_list *list, char **one_arg);
char	*add_one_symbol_in_end(char *str, char c);
void	parse_command(t_all *all, t_list *list);
t_list	*create_list(char **envp);
void	output_list(t_list *list, t_all *all, int i);
void	get_pwd(t_all *all, int i);
void	get_exit(void);
void	dup_fd(t_all *all, int i);
void	close_fd(t_all *all, int i);
void	ft_echo(t_all *all, int i);
void	another_com(t_all *all, int i);
void	add_export(t_list *list, t_all *all);
void	unset(t_list *list, t_all *all);
void	sort_export(t_list *list, t_all *all, int i);
char	*put_end_of_string(void);
char	*add_one_symbol_in_end(char *str, char c);
t_all	*create_struct(void);
int		add_in_struct(t_all *all);
void	clean_struct(t_all *all);
void	print_struct(t_all *all);
int		skip_space(char *str, int i);
int		check_errors(char *str);
void	check_build_in_command(t_all *all);

#endif
