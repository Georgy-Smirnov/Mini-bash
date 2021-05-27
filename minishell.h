#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct		s_echo
{
	char			*s_q;	// 1 кавычка
	char			*d_q;	// двойная кавычка

}					t_echo;

typedef struct		s_spec
{
	short int		pipe;	// |
	short int		s_l;	// >
	short int		s_m;	// <
	short int		d_l;	// >>
	short int		end;	// ;

}					t_spec;

typedef struct		s_arg
{
	char			*str;
	char			**another;

}					t_arg;

typedef struct		s_command
{
	short int		echo;	//флаг echo
	short int		n;		//флаг -n для echo
	short int		cd;
	short int		pwd;
	short int		exp;
	short int		exp_add; // ели ноль, то просто вывод отсортированного енв, если 1, значит добавить в енв
	short int		unset;
	short int		exit;
	short int		env;
	short int		another; // другая команда, поиск бинарника



}					t_command;

typedef struct		s_all
{
	short int		i;
	t_echo			echo;
	t_spec			spec;
	t_command		com;

}					t_all;

void				manage_export(char *name_varible, char *value_varible, char **envp, t_all *all);
#endif