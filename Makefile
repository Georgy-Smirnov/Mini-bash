#==================================>COLORS<====================================#

_RED		=	\e[31m
_YELLOW		=	\e[33m
_GREEN		=	\e[32m
_END		=	\e[0m

#==================================>FILES<=====================================#

SRC			=	main.c \
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

SRCS		=	$(SRC)

#===============================>COMPILATIONS<=================================#

GCC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

TREMCAP		=	-ltermcap

#===================================>DELETE<===================================#

RM			=	rm -rf

#=================================>DIRECTORIES<================================#

DIR_HEAD	=	./includes

LIB_HEAD	=	./libft/Libft.a

#===============================>COMPILED_SOURCES<=============================#

OBJS		=	${SRCS:%.c=%.o}

NAME		=	minishell

#================================>COMPILED_RULES<==============================#

all:			${NAME}

${NAME}:		${OBJS}
				@${MAKE} -C ./libft
				@${GCC} ${CFLAG} -o ${NAME} ${OBJS} ${LIB_HEAD} ${TREMCAP}
				@printf "\033[2K\r${_GREEN} Minishell create: '${NAME}'. ${_END}✅\n"

#===========================>COMPILED_SOURCES_RULES<===========================#

%.o:			%.c
				@$(GCC) $(CFLAGS) -I $(DIR_HEAD) -c $< -o $@
				@printf "\033[2K\r$(_YELLOW) Compiling $< $(_END)⌛"

#===================================>NORM_RULES<===============================#

norm:
				@norminette .			

#====================================>CLEAN_RULES<=============================#

clean:
			@make clean -C ./libft
			@rm -f ${OBJS}
			@printf "\033[2K\r${_RED} '".o"' has been deleted. ${_END}🗑️\n"

fclean:		clean
			@make fclean -C ./libft
			@rm -f ${NAME}
			@printf "\033[2K\r${_RED} '"${NAME}"' has been deleted. ${_END}🗑️\n"

re:			fclean all

.PHONY: all clean fclean re
