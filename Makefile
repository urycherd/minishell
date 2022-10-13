NAME			=	minishell

SRCSDIR			=	./srcs

OBJSDIR			=	./objs

SRCS			=	minishell.c	signals.c lexer.c utils.c executor.c executer_bin.c expansions.c\
					builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c heredoc.c\
					builtins/export_arg.c builtins/export.c builtins/pwd.c builtins/unset.c executor_2.c

OBJS			=	$(addprefix $(OBJSDIR)/,$(SRCS:.c=.o))

LIBFT			=	./libft/libft.a

HEADER			=	incs/minishell.h

MAKE			= 	Makefile

LIBC			=	ar rc
LIBR			=	ranlib

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror -fsanitize=address -g

RFLAGS			=	-lreadline\
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