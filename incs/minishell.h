/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 22:43:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/09/09 17:08:27 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
	
# include <curses.h>
# include <term.h>

# define MAX_PATH 256 


typedef struct s_info
{
	// t_builtin_ptr	builthes[7];
	// char			builtin_names[7];
	// char			**envp;
	// t_list			envpp_list;
	// char			envp_f;
	char			exit_f;
	// int				status;
	
}		t_info;

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}		t_list;

void	deal_with_signals(void);
int		ft_echo(char **args);
int		ft_env(t_list *env);
int		ft_pwd(void);
int		ft_echo(char **args);



#endif