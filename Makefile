# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/08 18:36:28 by qsergean          #+#    #+#              #
#    Updated: 2022/08/14 23:57:29 by qsergean         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

SRCSDIR			=	./srcs
OBJSDIR			=	./objs

SRCS			=	minishell.c
OBJS			=	$(addprefix $(OBJSDIR)/,$(SRCS:.c=.o))

LIBFT			=	

HEADER			=	incs/minishell.h
MAKE			= 	Makefile

LIBC			=	ar rc
LIBR			=	ranlib

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror\
					-lreadline\
					-L/Users/$(USER)/.brew/Cellar/readline/8.1.2/lib\
					-I/Users/$(USER)/.brew/Cellar/readline/8.1.2/include
RM				=	rm -rf

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c ${HEADER} ${MAKE}
	${CC} ${CFLAGS} -c $< -o $@ 

all: ${NAME} 

${NAME}: ${OBJS}
	$(CC) ${CFLAGS} -o $(NAME) $(OBJS)

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re .c.o