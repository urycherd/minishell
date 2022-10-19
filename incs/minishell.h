/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 22:43:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/10/19 20:52:50 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <curses.h>
# include <term.h>

# define MAX_PATH 256

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
};

typedef struct s_redir
{
	char			**filename;
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
	t_list	*redir;
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
	pid_t	pid1;
	pid_t	pid2;
}	t_ppx;

/*
** lexer
*/
int		lexer(t_main **main, char *input);
void	deal_with_dollar(t_main *main, char *input, int *i, t_lexem **content);
void	deal_with_redir(char *input, int *i, t_lexem **content);
void	spc_nwln_pipe(char *input, int *i, t_lexem **content);
void	deal_with_quotes(char *input, int *i, t_lexem **content);
void	handle_expansions(t_main **main);
void	deal_with_word(char *input, int *i, t_lexem **content);
char	*ft_getenv(t_list *env, char *request);

/*
** parser
*/
int		preparsing(t_main **main, char *input);
void	parser(t_main **main);
int		is_redir(t_list *lexem);
int		get_num_of_args(t_list *lexem);
int		get_num_of_redirs(t_list *lexem);
t_list	*get_lexem_wo_sep(t_list *lexem);

/*
** executor
*/
int		executor(t_main *main);
int		ft_excv(t_main *main, char	**cmd_args, t_list	*next);
int		deal_heredoc(t_redir *redir, int i);
void	dup_close(int fd_old, int fd_new);
int		check_redir(t_list *redir_list);
int		take_your_builtin(t_main *main, char **args);

/*
** builtins
*/
int		ft_cd(t_main *main, char **args);
int		ft_echo(char **args);
int		ft_env(t_list *env, char **arg);
int		ft_exit(t_main *main, char **arg);
int		ft_export(t_main **main, char **arg);
int		ft_unset(t_main **main, char **arg);
int		ft_pwd(void);

/*
** builtins' helpers
*/
char	*ft_detect_key(char *str);
int		arg_export(t_main *main, char *arg);
int		rewrite_key(char *key, char *path, t_main *main);
char	**lst_to_arr_str(t_list *env, int size);

/*
** utils
*/
void	deal_with_signals(t_main **main);
int		change_to_spaces_and_check_quotes(char **str);
int		get_word_len(char *str, int i, char c, int flag);
void	make_env_list(t_main **main, char **envp);
char	*ft_strjoin_mod(char *s1, char *s2);
int		print_error(char *cmd, char *arg, char *error_name);
int		print_error_nocmd(char *arg, char *error_name);

#endif
