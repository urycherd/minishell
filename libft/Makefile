# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 13:38:47 by qsergean          #+#    #+#              #
#    Updated: 2022/09/13 23:15:23 by qsergean         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRCS	=	ft_isalpha.c		ft_isdigit.c		ft_isalnum.c\
			ft_isascii.c		ft_isprint.c		ft_strlen.c\
			ft_memset.c			ft_bzero.c			ft_memcpy.c\
			ft_memmove.c		ft_strlcpy.c		ft_strlcat.c\
			ft_toupper.c		ft_tolower.c		ft_strchr.c\
			ft_strrchr.c		ft_strncmp.c		ft_memchr.c\
			ft_memcmp.c			ft_strnstr.c		ft_atoi.c\
			ft_calloc.c			ft_strdup.c			ft_substr.c\
			ft_strjoin.c		ft_strtrim.c		ft_split.c\
			ft_itoa.c			ft_strmapi.c		ft_striteri.c\
			ft_putchar_fd.c		ft_putstr_fd.c		ft_putendl_fd.c\
			ft_putnbr_fd.c      ft_strcmp.c\
			ft_lstnew.c			ft_lstadd_front.c	ft_lstsize.c\
			ft_lstlast.c		ft_lstadd_back.c	ft_lstdelone.c\
			ft_lstclear.c		ft_lstiter.c		ft_lstmap.c 

OBJS	= ${SRCS:.c=.o}
HEADER	= ../incs/libft.h

LIBC	= ar rc
LIBR	= ranlib

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@ 

all: ${NAME}

${NAME}: ${OBJS} ${HEADER}
	${LIBC} ${NAME} ${OBJS}
	${LIBR} ${NAME}

bonus: ${NAME}
 
clean:
	${RM} ${OBJS} ${OBJS_B}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus .c.o
