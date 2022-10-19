/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:23:36 by urycherd          #+#    #+#             */
/*   Updated: 2022/10/19 20:57:48 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	rec_ex(t_main *main, t_list *cmd, int *true_fd)
{
	t_ppx	ppx;
	int		red;
	char	**args;
	int		orig_fd[2];

	orig_fd[1] = dup(1);
	orig_fd[0] = dup(0);
	args = ((t_command *)(cmd->content))->args;
	if (pipe(ppx.fd) == -1)
		return (print_error_nocmd(NULL, "pipe doesn't work"));
	if (cmd->next)
		dup_close(ppx.fd[1], 1);
	else
		dup_close(true_fd[1], 1);
	red = check_redir(((t_command *)(cmd->content))->redir);
	if (!red)
	{
		close(orig_fd[1]);
		close(orig_fd[0]);
	}
	if (take_your_builtin(main, args) < 0)
		ft_excv(main, args, cmd->next);
	if (red)
		dup_close(red, 1);
	if (!cmd->next)
	{
		dup_close(true_fd[0], 0);
		close(ppx.fd[1]);
		close(ppx.fd[0]);
		if (red)
		{
			dup_close(orig_fd[0], 0);
			dup_close(orig_fd[1], 1);
		}
		return (0);
	}
	dup_close(ppx.fd[0], 0);
	if (red)
	{
		dup_close(orig_fd[0], 0);
		dup_close(orig_fd[1], 1);
	}
	return (rec_ex(main, cmd->next, true_fd));
}

int	executor(t_main *main)
{
	char	**args;
	t_list	*cmd;
	int		true_fd[2];

	cmd = main->commands;
	if (cmd)
		args = ((t_command *)(cmd->content))->args;
	true_fd[0] = dup(0);
	true_fd[1] = dup(1);
	if (cmd)
		if (rec_ex(main, cmd, true_fd))
			return (1);
	return (0);
}
