#include "../../includes/minishell.h"

void	get_exit(void)
{
	write(1, "exit\n", 5);
	exit(1);
}
