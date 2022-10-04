/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:23:36 by urycherd          #+#    #+#             */
/*   Updated: 2022/10/04 17:32:20 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	take_your_builtin(t_main *main)
{
	char	**args;

	args = ((t_command *)(main->commands->content))->args;
	if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(main, args));
	else if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(args));
	else if (!ft_strcmp(args[0], "env"))
		return (ft_env(main->env, args));
	else if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(main, args));
	else if (!ft_strcmp(args[0], "export"))
		return (ft_export(&main, args));
	else if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(&main, args));
	return (-1);
}

int	executor(t_main *main)
{
	char	**args;
	t_list	*cmd;

	args = ((t_command *)(main->commands->content))->args;
	cmd = main->commands;
	while (cmd)
	{
		// check if redirect
		// 		dup2
		if (!main->commands->next)
		{
			if (take_your_builtin(main) >= 0)
				return (0);
			if (ft_excv(main, args))
				return (0);
		}
		// else
		// 	if (ft_pipex())
		// 		return (1);
		cmd = cmd->next;
	}
	
	return (0);
}
