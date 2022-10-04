/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 22:43:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/10/04 17:13:40 by urycherd         ###   ########.fr       */
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

typedef struct s_ppx
{
	int		fd[2];
	char	**cmd_paths;
	char	**envp;
	char	*path;
	char	*cmd;
	pid_t	pid;
}	t_ppx;

void	deal_with_signals(void);

int		lexer(t_main **main, char *input);
void	deal_with_dollar(char *input, int *i, t_lexem **content);
int		executor(t_main *main);
int		ft_excv(t_main *main, char	**cmd_args);


int		change_to_spaces_and_check_quotes(char **str);
int		get_word_len(char *str, int i, char c, int flag);
void	make_env_list(t_main **main, char **envp);
char	*ft_strjoin_mod(char *s1, char *s2);
int		print_error(char *cmd, char *arg, char *error_name);
int		print_error_nocmd(char *arg, char *error_name);


int		ft_cd(t_main *main, char **args);
int		ft_echo(char **args);
int		ft_env(t_list *env, char **arg);
int		ft_exit(t_main *main, char **arg);
int		ft_export(t_main **main, char **arg);
int		ft_unset(t_main **main, char **arg);
int		ft_pwd(void);

//sup functions for builtin
char	*ft_detect_key(char *str);
int		arg_export(t_main *main, char *arg);
int		rewrite_key(char *key, char *path, t_main *main);
char	**lst_to_arr_str(t_list *env, int size);


#endif