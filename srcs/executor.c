/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:23:36 by urycherd          #+#    #+#             */
/*   Updated: 2022/10/12 12:01:59 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	dup_close(int fd_old, int fd_new)
{
	dup2(fd_old, fd_new);
	close(fd_old);
}

int	check_redir(t_list *redir_list)
{
	int		fd;
	int		i;
	t_redir	*redir;

	i = 0;
	fd = 0;
	while (redir_list)
	{
		redir = ((t_redir *)(redir_list->content));
		if (redir->token == TOKEN_OUT_REDIR)
		{
			fd = open(redir->filename[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (fd < 0)
				exit (1);
			dup_close(fd, 1);
		}
		else if (redir->token == TOKEN_OUT_REDIR_APPEND)
		{
			fd = open(redir->filename[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (fd < 0)
				exit (1);
			dup_close(fd, 1);
		}
		else if (redir->token == TOKEN_IN_REDIR)
		{
			fd = open(redir->filename[i], O_RDONLY, 0644);
			if (fd < 0)
				exit (1);
			dup_close(fd, 0);
		}
		// else if (redir->token == TOKEN_HEREDOC)
		// 	deal_heredoc(redir, i);
		i++;
		redir_list = redir_list->next;
	}
	return (fd);
}

int	take_your_builtin(t_main *main, char **args)
{
	if (args == NULL)
		return (-1);
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

int	rec_ex(t_main *main, t_list *cmd, int *true_fd)
{
	t_ppx	ppx;
	char	**args;

	args = ((t_command *)(cmd->content))->args;
	if (pipe(ppx.fd) == -1)
		return (print_error_nocmd(NULL, "pipe doesn't work"));
	if (cmd->next)
		dup_close(ppx.fd[1], 1);
	else
		dup_close(true_fd[1], 1);
	check_redir(((t_command *)(cmd->content))->redir);
	if (take_your_builtin(main, args) < 0)
		if (ft_excv(main, args, cmd->next))
			return (print_error_nocmd(NULL, "command problemmmmm"));
	if (!cmd->next)
	{
		dup_close(true_fd[0], 0);
		close(ppx.fd[1]);
		close(ppx.fd[0]);
		return (0);
	}
	dup_close(ppx.fd[0], 0);
	return (rec_ex(main, cmd->next, true_fd));
}
//   redit + builtin without pipe -> 
int	executor(t_main *main)
{
	char	**args;
	t_list	*cmd;
	int		true_fd[2];

	args = ((t_command *)(main->commands->content))->args;
	cmd = main->commands;
	true_fd[0] = dup(0);
	true_fd[1] = dup(1);
	if (cmd)
		if (rec_ex(main, cmd, true_fd))
			return (1);
	// dup_close(true_fd[0], 0);
	// dup_close(true_fd[1], 1);
	return (0);
}
