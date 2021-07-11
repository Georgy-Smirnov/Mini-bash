#!/bin/bash
gcc main.c srcs/*.c srcs/logic/*.c srcs/parsing/*.c srcs/utils/*.c libft/Libft.a -ltermcap && ./a.out