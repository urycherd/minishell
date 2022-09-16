/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 22:43:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/09/16 22:26:55 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <curses.h>
# include <term.h>

# define MAX_PATH 256
# ifndef OK
#  define OK 0
# endif

enum e_tokens
{
	TOKEN_SEP,
	TOKEN_NEWLINE,
	TOKEN_PIPE,
	TOKEN_WORD,
	TOKEN_OUT_REDIR,
	TOKEN_OUT_REDIR_APPEND,
	TOKEN_IN_REDIR,
	TOKEN_HEREDOC,
	TOKEN_ENV,
	TOKEN_L_BRACKET,
	TOKEN_R_BRACKET
};

typedef struct s_lexem
{
	char			*str;
	enum e_tokens	token;
	int				len;
}	t_lexem;

typedef struct s_main
{
	t_list	*env;
	t_list	*lexems;
}	t_main;

typedef struct s_info
{
	// t_builtin_ptr	builthes[7];
	// char			builtin_names[7];
	// char			**envp;
	// t_list			envpp_list;
	// char			envp_f;
	char			exit_f;
	// int				status;
}	t_info;

void	deal_with_signals(void);
int		ft_echo(char **args);
int		ft_env(t_list *env);
int		ft_pwd(void);
int		ft_echo(char **args);

#endif