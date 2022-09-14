/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 22:43:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/09/14 23:39:07 by qsergean         ###   ########.fr       */
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

typedef struct s_main
{
	t_list	*env;
	t_list	*lexems;
	int		d_quotes;
	int		s_quotes;
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