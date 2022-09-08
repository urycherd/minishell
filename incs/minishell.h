/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 22:43:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/09/08 12:56:47 by urycherd         ###   ########.fr       */
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

void	deal_with_signals(void);
int		ft_echo(char **args);


#endif