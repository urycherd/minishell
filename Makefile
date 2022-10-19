NAME			=	minishell

SRCSDIR			=	./srcs

OBJSDIR			=	./objs

SRCS			=	minishell.c\
					\
					builtins/cd.c	builtins/echo.c		builtins/env.c	builtins/exit.c\
					builtins/pwd.c	builtins/export.c	builtins/unset.c\
					builtins/export_arg.c\
					\
					exec/heredoc.c	exec/executor_1.c	exec/executor_2.c\
					exec/exec_bin.c\
					\
					lexer/lexer.c	lexer/dollar.c	lexer/cases.c	lexer/expansions.c\
					\
					parser/preparser.c	parser/parse_utils.c\
					parser/parser.c\
					\
					utils/utils.c	utils/signals.c

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
	@mkdir -p $(OBJSDIR)
	@mkdir -p $(addprefix $(OBJSDIR)/,builtins)
	@mkdir -p $(addprefix $(OBJSDIR)/,exec)
	@mkdir -p $(addprefix $(OBJSDIR)/,lexer)
	@mkdir -p $(addprefix $(OBJSDIR)/,parser)
	@mkdir -p $(addprefix $(OBJSDIR)/,utils)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c ${HEADER} ${MAKE}
	@${CC} ${CFLAGS} -c $< -o $@

$(LIBFT):
	@echo "Making libft..."
	@cd libft && make bonus
	@echo "Done!\n"

${NAME}: $(OBJSDIR) $(OBJS)
	@echo "Making minishell..."
	@ $(CC) ${CFLAGS} $(RFLAGS) $(LIBFT) -o $(NAME) $(OBJS)
	@echo "Done!" 

# ${NAME}: $(OBJS) $(OBJSDIR)
# 	$(CC) ${CFLAGS} $(OBJS) $(RFLAGS) $(LIBFT) -o $(NAME)

clean:
	@echo "Cleaning..."
	@${RM} ${OBJS}
	@${RM} ${OBJSDIR}
	@cd libft && make clean
	@echo "Done!\n"

fclean: clean
	@echo "Full cleaning..."
	@${RM} ${NAME}
	@cd libft && make fclean
	@echo "Done!\n"

re: fclean all

.PHONY: all clean fclean re .c.o