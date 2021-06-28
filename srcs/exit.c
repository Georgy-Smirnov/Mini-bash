#include "../includes/minishell.h"

void    get_exit(t_all *all)
{
    write(1, "exit\n", 5);
    exit(1); 
}