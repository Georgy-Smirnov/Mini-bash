#include "../../includes/minishell.h"

void	print_d_array(char **hystory)
{
	int	i;

	i = 0;
	if (hystory == NULL)
		ft_putstr_fd("!!!NULL!!!", 1);
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

void	print_struct(t_all *all)
{
	int i = 0;

	printf("*******************************\n");
	printf("count: %d\n", all->count);
	printf("*******************************\n\n\n");
	while (i <= all->count)
	{
		printf("*******************************\n");
		printf("***********struct %d************\n", i);
		printf("*******************************\n");
		printf("**********t_command**************\n");
		printf("exp: %d\n", all->com[i].exp);
		printf("exp_add: %d\n", all->com[i].exp_add);
		printf("unset: %d\n", all->com[i].unset);
		printf("env: %d\n", all->com[i].env);
		printf("echo: %d\n", all->com[i].echo);
		printf("n: %d\n", all->com[i].n);
		printf("cd: %d\n", all->com[i].cd);
		printf("pwd: %d\n", all->com[i].pwd);
		printf("exit: %d\n", all->com[i].exit);
		printf("another: %d\n", all->com[i].another);
		printf("*********t_flags************\n");
		printf("pipe: %d\n", all->flags[i].pipe);
		printf("less_than: %d\n", all->flags[i].less_than);
		printf("greater_than: %d\n", all->flags[i].greater_than);
		printf("d_greater_than: %d\n", all->flags[i].d_greater_than);
		printf("***********t_arg***************\n");
		print_d_array(all->arg[i].arguments);
		printf("--------------\n");
		printf("fd 0: %d; fd 1: %d;\n", all->arg[i].fd[0], all->arg[i].fd[1]);
		printf("*******************************\n");
		i++;
	}
}

void	check_build_in_command(t_all *all)
{
	if (all->arg[all->count].arguments != NULL)
	{
		if (!ft_strncmp(all->arg[all->count].arguments[0], "export", 6) && all->arg[all->count].arguments[1] == NULL)
			all->com[all->count].exp = 1;
		else if (!ft_strncmp(all->arg[all->count].arguments[0], "export", 6))
		{
			all->com[all->count].exp = 0;
			all->com[all->count].exp_add = 1;
		}
		else if (!ft_strncmp(all->arg[all->count].arguments[0], "unset", 5))
			all->com[all->count].unset = 1;
		else if (!ft_strncmp(all->arg[all->count].arguments[0], "env", 3))
			all->com[all->count].env = 1;
		else if (!ft_strncmp(all->arg[all->count].arguments[0], "cd", 2))
			all->com[all->count].cd = 2;
		else if (!ft_strncmp(all->arg[all->count].arguments[0], "pwd", 3))
			all->com[all->count].pwd = 1;
		else if (!ft_strncmp(all->arg[all->count].arguments[0], "exit", 4))
			all->com[all->count].exit = 1;
		else if (!ft_strncmp(all->arg[all->count].arguments[0], "echo", 4))
		{
			all->com[all->count].echo = 1;
			if (all->arg[all->count].arguments[1] != NULL && !ft_strncmp(all->arg[all->count].arguments[1], "-n", 2))
				all->com[all->count].n = 1;
		}
	}
}

char *put_name_file(char *str)
{
	char *rez;
	int i;
	int q;
	int count;

	i = 0;
	count = 0;
	if (str[0] == '/')
	{
		while (str[i])
		{
			if (str[i] == '/')
			{
				count = 0;
				q = i;
			}
			count++;
			i++;
		}
		i= 0;
		rez = (char *)malloc(sizeof(char) * count + 1);
		if (rez == NULL)
			return (rez);
		q++;
		while (str[q])
		{
			rez[i] = str[q];
			i++;
			q++;
		}
		rez[i] = 0;
		return (rez);
	}
	else
	{
		rez = ft_strdup(str);
		return (rez);
	}
		
}

int	open_fd(t_all *all)
{
	int i = 0;
	int tmp[2];
	int fd = -2;
	char *tmp_str;
	
	while (i < all->count)
	{
		if (i < all->count)
			tmp_str = put_name_file(all->arg[i + 1].arguments[0]);
		if (all->flags[i].pipe)
		{
			pipe(tmp);
			all->arg[i].fd[1] = tmp[1];
			all->arg[i + 1].fd[0] = tmp[0];
		}
		if (all->flags[i].greater_than)
		{
			if (fd != -2)
				close(fd);
			fd = open(tmp_str, O_CREAT | O_RDWR |  O_TRUNC, 0777);
			if (fd == -1)
				return (0);
			all->arg[i].fd[1] = fd;
		}
		if (all->flags[i].d_greater_than)
		{
			if (fd != -2)
				close(fd);
			fd = open(tmp_str, O_CREAT | O_RDWR |  O_APPEND, 0777);
			if (fd == -1)
				return (0);
			all->arg[i].fd[1] = fd;
		}
		if (all->flags[i].less_than)
		{
			if (fd != -2)
				close(fd);
			fd = open(tmp_str, O_CREAT | O_RDWR, 0777);
			if (fd == -1)
				return (0);
			all->arg[i].fd[0] = fd;
		}
		if (i < all->count)
			free(tmp_str);
		i++;
	}
	return (1);
}

int	start_work_command(t_all *all, t_list *list)
{
	if (open_fd(all) == 0)
		return (0);
	parse_command(all, list);
	// print_struct(all);
	return (1);
}