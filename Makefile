
SRCS		=	main.c \
				srcs/parsing/add_in_struct.c \
				srcs/parsing/change_path.c \
				srcs/parsing/check_errors.c \
				srcs/parsing/create_clean_struct.c \
				srcs/parsing/do_if_quotes.c \
				srcs/parsing/open_fd.c \
				srcs/parsing/press_key.c  \
				srcs/parsing/put_variable.c \
				srcs/parsing/read.c \
				srcs/parsing/start_parse_command.c \
				srcs/parsing/start_work_command.c \
				srcs/parsing/utils.c \
				srcs/parsing/write_one_arg.c \
				srcs/logic/another_com.c \
				srcs/logic/echo.c \
				srcs/logic/env.c \
				srcs/logic/exit.c \
				srcs/logic/export.c \
				srcs/logic/export_add.c \
				srcs/logic/parse_command.c \
				srcs/logic/pwd.c \
				srcs/logic/unset.c \
				srcs/utils/create_list.c \
				srcs/utils/dup_close_fd.c \

NAME		=	minishell

GCC			=	gcc

CFLAG		=	-Wall -Werror -Wextra

OBJS		=	${SRCS:%.c=%.o}

all:			${NAME}

${NAME}:		${OBJS}
				${MAKE} -C ./libft
				${GCC} ${CFLAG} -o ${NAME} ${OBJS} libft/Libft.a -ltermcap

%.o:			%.c
				${GCC} ${CFLAG} -c $< -o $@

clean:
			make clean -C ./libft
			rm -f ${OBJS}

fclean:		clean
			make fclean -C ./libft
			rm -f ${NAME}

re:			fclean all

.PHONY: all clean fclean re


