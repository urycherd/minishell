# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/08 18:36:28 by qsergean          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2022/09/28 21:05:38 by qsergean         ###   ########.fr        #
=======
#    Updated: 2022/09/28 21:43:58 by urycherd         ###   ########.fr        #
>>>>>>> da94fca7a618b6ba935784c146f2b548613f47a2
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

SRCSDIR			=	./srcs

OBJSDIR			=	./objs

<<<<<<< HEAD
SRCS			=	minishell.c		signals.c		lexer.c\
					utils.c			builtins/env.c
# builtins/export_arg.c	builtins/export.c 
=======
SRCS			=	minishell.c	signals.c	lexer.c\
					utils.c	builtins/env.c builtins/echo.c\
					builtins/export_arg.c builtins/export.c 
>>>>>>> da94fca7a618b6ba935784c146f2b548613f47a2

OBJS			=	$(addprefix $(OBJSDIR)/,$(SRCS:.c=.o))

LIBFT			=	./libft/libft.a

HEADER			=	incs/minishell.h

MAKE			= 	Makefile

LIBC			=	ar rc
LIBR			=	ranlib

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror -fsanitize=address -g

RFLAGS			=	-lreadline\
					-L/Users/$(USER)/.brew/Cellar/readline/8.1.2/lib\
					-I/Users/$(USER)/.brew/Cellar/readline/8.1.2/include\
					-ltermcap

RM				=	rm -rf

all: $(LIBFT) ${NAME} 

$(OBJSDIR):
	mkdir -p $(OBJSDIR)
	mkdir -p $(addprefix $(OBJSDIR)/,builtins)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c ${HEADER} ${MAKE}
	${CC} ${CFLAGS} -c $< -o $@ 

$(LIBFT):
	@cd libft && make bonus

${NAME}: $(OBJSDIR) $(OBJS)
	@ $(CC) ${CFLAGS} $(RFLAGS) $(LIBFT) -o $(NAME) $(OBJS)

# ${NAME}: $(OBJS) $(OBJSDIR)
# 	$(CC) ${CFLAGS} $(OBJS) $(RFLAGS) $(LIBFT) -o $(NAME)

clean:
	${RM} ${OBJS}
	${RM} ${OBJSDIR}
	@cd libft && make clean

fclean: clean
	${RM} ${NAME}
	@cd libft && make fclean

re: fclean all

.PHONY: all clean fclean re .c.o