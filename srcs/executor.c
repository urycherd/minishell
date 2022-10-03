/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:23:36 by urycherd          #+#    #+#             */
/*   Updated: 2022/10/03 21:53:35 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	take_your_builtin(t_main *main)
{
	char	**args;

	args = ((t_command *)(main->commands->content))->args;
	if (!ft_strcmp(args[0], "cd"))
		ft_cd(main, args);
	else if (!ft_strcmp(args[0], "echo"))
		ft_echo(args);
	else if (!ft_strcmp(args[0], "env"))
		ft_env(main->env, args);
	else if (!ft_strcmp(args[0], "exit"))
		ft_exit(main, args);
	else if (!ft_strcmp(args[0], "export"))
		ft_export(&main, args);
	else if (!ft_strcmp(args[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(args[0], "unset"))
		ft_unset(&main, args);
	return (0);
}

int	executor(t_main *main)
{
	take_your_builtin(main);
	return (0);
}
