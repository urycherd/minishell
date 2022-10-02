/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 22:43:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/10/02 18:00:19 by qsergean         ###   ########.fr       */
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
	TOKEN_DQUOTE,
	TOKEN_OUT_REDIR,
	TOKEN_OUT_REDIR_APPEND,
	TOKEN_IN_REDIR,
	TOKEN_HEREDOC,
	// TOKEN_ENV,
	// TOKEN_L_BRACKET,
	// TOKEN_R_BRACKET
};

typedef struct s_redir
{
	char			*filename;
	enum e_tokens	token;
}	t_redir;

typedef struct s_lexem
{
	char			*str;
	enum e_tokens	token;
	int				len;
}	t_lexem;

typedef struct s_command
{
	char	**args;
	int		file_open;
	int		file_close;
}	t_command;

typedef struct s_main
{
	t_list	*env;
	t_list	*lexems;
	t_list	*commands;
	int		exit_f;
	int		ret;
}	t_main;

typedef struct s_info
{
	// t_builtin_ptr	builthes[7];
	// char			builtin_names[7];
	t_list			*env;
	// t_list			envpp_list;
	// char			envp_f;
	// char			exit_f;
	// int				status;
}	t_info;

int		ft_echo(char **args);
int		ft_env(t_list *env);
int		ft_pwd(void);
int		ft_echo(char **args);

void	deal_with_signals(void);

int		lexer(t_main **main, char *input);
void	deal_with_dollar(char *input, int *i, t_lexem **content);

int		change_to_spaces_and_check_quotes(char **str);
int		get_word_len(char *str, int i, char c, int flag);
void	make_env_list(t_main **main, char **envp);
char	*ft_strjoin_mod(char *s1, char *s2);

int		ft_env(t_list *env);
int		ft_pwd(void);
int		ft_export(t_main **main, char **arg);
int		ft_echo(char **args);

//sup functions for builtin
char	*ft_detect_key(char *str);
int		arg_export(t_main *main, char *arg);

#endif