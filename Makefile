# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/08 18:36:28 by qsergean          #+#    #+#              #
#    Updated: 2022/09/13 23:29:34 by qsergean         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

SRCSDIR			=	./srcs
OBJSDIR			=	./objs

SRCS			=	minishell.c	signals.c
OBJS			=	$(addprefix $(OBJSDIR)/,$(SRCS:.c=.o))

LIBFT			=	./libft/libft.a

HEADER			=	incs/minishell.h
MAKE			= 	Makefile

LIBC			=	ar rc
LIBR			=	ranlib

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
RFLAGS			=	-lreadline\
					-L/Users/$(USER)/.brew/Cellar/readline/8.1.2/lib\
					-I/Users/$(USER)/.brew/Cellar/readline/8.1.2/include\
					-ltermcap
RM				=	rm -rf

all: $(LIBFT) ${NAME} 

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c ${HEADER} ${MAKE} 
	${CC} ${CFLAGS} -c $< -o $@ 

$(LIBFT):
	@cd libft && make bonus

${NAME}: $(OBJS) $(OBJSDIR)
	$(CC) ${CFLAGS} $(RFLAGS) $(LIBFT) -o $(NAME) $(OBJS)

# ${NAME}: $(OBJS) $(OBJSDIR)
# 	$(CC) ${CFLAGS} $(OBJS) $(RFLAGS) $(LIBFT) -o $(NAME)

clean:
	${RM} ${OBJS}
	@cd libft && make clean

fclean: clean
	${RM} ${NAME}
	@cd libft && make fclean

re: fclean all

.PHONY: all clean fclean re .c.o