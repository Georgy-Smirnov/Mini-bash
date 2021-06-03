SRCS		=	main.c \
				srcs/read.c \
				srcs/start_parse_command.c \
				srcs/check_errors.c \
				srcs/add_in_struct.c \
				srcs/do_if_quotes.c \
				srcs/create_clean_struct.c \
				srcs/start_work_command.c \
				srcs/export.c \
				srcs/unset.c

NAME		=	minishell

OBJS		=	${SRCS:%.c=%.o}

all:			${NAME}

${NAME}:		${OBJS}
				gcc -o ${NAME} ${OBJS} libft/Libft.a -ltermcap

%.o:			%.c
				gcc -c $< -o $@

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY: all clean fclean re

#${MAKE} -C ./libft #

