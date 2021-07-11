#include "includes/minishell.h"

void	myquit(int sig)
{
	int		pid;
	int		status;

	(void)sig;
	pid = waitpid(-1, &status, WNOHANG);
	if (!pid)
		ft_putendl_fd("Quit: 3", 1);
}

void	mysigint(int sig)
{
	int		pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		if (pid)
			write (1, "\e[1;32mMinishell% \e[0m", 22);
	}
}

char	*put_term_name(char **env)
{
	char	*rez;
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (strncmp(env[i], "TERM=", 5) == 0)
		{
			rez = ft_strdup(&env[i][5]);
			if (rez == NULL)
				return (NULL);
		}
		i++;
	}
	return (rez);
}

int	term_my_ref(struct termios term, int flag, char **env)
{
	char	*term_name;

	term_name = put_term_name(env);
	if (term_name == NULL)
		return (0);
	if (isatty(0) == 0)
		return (0);
	if (tcgetattr(0, &term) == -1)
		return (0);
	if (flag == 1)
		term.c_lflag &= ~(ECHO | ICANON);
	else if (flag == 2)
		term.c_lflag |= (ECHO | ICANON);
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (0);
	tgetent(0, term_name);
	free (term_name);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	struct termios	term;

	signal(SIGQUIT, myquit);
	signal(SIGINT, mysigint);
	if (!term_my_ref(term, 1, env))
		return (0);
	if (start_minishell(term, env) != 1)
		return (0);
	if (!term_my_ref(term, 2, env))
		return (0);
}
