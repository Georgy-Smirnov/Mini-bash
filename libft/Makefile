# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kjaco <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/01 20:20:47 by kjaco             #+#    #+#              #
#    Updated: 2021/05/26 14:41:43 by kjaco            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## START_MAKEFILE ##

#==================================>FILES<=====================================#

SRC			= ft_memset.c \
			  ft_bzero.c \
			  ft_memcpy.c \
			  ft_memccpy.c \
			  ft_memmove.c \
			  ft_memchr.c \
			  ft_memcmp.c \
			  ft_strlen.c \
			  ft_strlcpy.c \
			  ft_strlcat.c \
			  ft_strchr.c \
			  ft_strrchr.c \
			  ft_strnstr.c \
			  ft_strncmp.c \
			  ft_strcmp.c \
			  ft_atoi.c \
			  ft_isalpha.c \
			  ft_isdigit.c \
			  ft_isalnum.c \
			  ft_isascii.c \
			  ft_isprint.c \
			  ft_toupper.c \
			  ft_tolower.c \
			  ft_calloc.c \
			  ft_strdup.c \
			  ft_substr.c \
			  ft_strjoin.c \
			  ft_strtrim.c \
			  ft_split.c \
			  ft_itoa.c \
			  ft_strmapi.c \
			  ft_putchar_fd.c \
			  ft_putstr_fd.c \
			  ft_putendl_fd.c \
			  ft_putnbr_fd.c \
			  ft_delbeforechar.c \
			  ft_strjoin_with_frees1.c \
			  ft_get_next_line.c \
			  ft_dellastchar.c \
			  ft_lstnew.c \
			  ft_lstadd_front.c \
			  ft_lstsize.c \
			  ft_lstlast.c \
			  ft_lstadd_back.c \
			  ft_lstdelone.c \
			  ft_lstclear.c \
			  ft_lstiter.c \
			  ft_lstmap.c

SRCS		=	$(SRC)

#===============================>COMPILATIONS<=================================#

GCC			=	gcc

AR			=	ar rc

CFLAGS		=	-Wall -Werror -Wextra

#===================================>DELETE<===================================#

RM			=	rm -rf

#=================================>DIRECTORIES<================================#

DIR_HEAD	=	./

DIR_SRCS	=	./

DIR_OBJS	=	./object_files/

#===============================>COMPILED_SOURCES<=============================#

OBJS		=	${SRCS:%.c=${DIR_OBJS}%.o}

NAME		=	Libft.a

#================================>COMPILED_RULES<==============================#


all:			${NAME}

${NAME}:		${OBJS}
				${AR} ${NAME} ${OBJS}
				ranlib ${NAME}

#===========================>COMPILED_SOURCES_RULES<===========================#

$(OBJS):		| $(DIR_OBJS)

$(DIR_OBJS)%.o: $(DIR_SRCS)%.c
				$(GCC) $(CFLAGS) -I $(DIR_HEAD) -c $< -o $@

$(DIR_OBJS):
				mkdir $(DIR_OBJS)

#===================================>NORM_RULES<===============================#

norm:
				norminette *.c
				norminette *.h				

#====================================>CLEAN_RULES<=============================#

clean:
				${RM} ${DIR_OBJS}

fclean:			clean	
				${RM} ${NAME}

re:				fclean all

.PHONY: all clean fclean norm re
