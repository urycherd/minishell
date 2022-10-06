/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:23:36 by urycherd          #+#    #+#             */
/*   Updated: 2022/10/05 20:38:21 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	take_your_builtin(t_main *main, char **args)
{
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

int	rec_ex(t_main *main, t_list *cmd, int true_fd)
{
	t_ppx	ppx;
	char	**args;

	args = ((t_command *)(cmd->content))->args;
	if (pipe(ppx.fd) == -1)
		return (print_error_nocmd(NULL, "pipe doesn't work"));
	// close(ppx.fd[0]); 
	if (cmd->next)
		ft_putnbr_fd(dup2(ppx.fd[1], 1), 2); // меняем запись вместо stdout (вывод) в pipe
	else
		dup2(true_fd, 1);
	if (take_your_builtin(main, args) < 0)
			if (ft_excv(main, args))
				return (1);
	write(2, "lol\n", 4);
	if (!cmd->next)
		return (0);
	close(ppx.fd[1]); // закрываю на запись
	ft_putnbr_fd(dup2(ppx.fd[0], 0), 2); // меняем чтение вместо stdin (ввод) в pipe
	return (rec_ex(main, cmd->next, true_fd));
}

int	executor(t_main *main)
{
	char	**args;
	t_list	*cmd;
	int		true_fd;

	args = ((t_command *)(main->commands->content))->args;
	cmd = main->commands;
	// check if redirect
	// 		dup2
	if (cmd && !cmd->next) // for 1 param
	{
		if (take_your_builtin(main, args) >= 0)
			return (0);
		if (ft_excv(main, args))
			return (0);
	}
	else
	{
		true_fd = dup(1);
		if (rec_ex(main, cmd, true_fd))
			return (1);
	}
	return (0);
}
