#!/bin/bash
gcc main.c srcs/*.c srcs/logic/*.c srcs/utils/*.c libft/Libft.a -ltermcap && ./a.out