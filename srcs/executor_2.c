/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:11:59 by urycherd          #+#    #+#             */
/*   Updated: 2022/10/13 22:26:23 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	dup_close(int fd_old, int fd_new)
{
	dup2(fd_old, fd_new);
	close(fd_old);
}

void	close_fd(int	*orig_fd)
{
	close(orig_fd[1]);
	close(orig_fd[0]);
}

void	check_dup_redir(int fd, char *file, int a)
{
	if (fd < 0)
		print_error_nocmd(file, "No such file or directory1");
	else
		dup_close(fd, a);
}

int	check_redir(t_list *redir_list)
{
	int		redir_exists;
	int		i;
	t_redir	*red;

	i = 0;
	redir_exists = 0;
	while (redir_list)
	{
		red = ((t_redir *)(redir_list->content));
		redir_exists = red->token;
		if (red->token == TOKEN_OUT_REDIR)
			check_dup_redir(open(red->filename[i],
					O_WRONLY | O_TRUNC | O_CREAT, 0644), red->filename[i], 1);
		else if (red->token == TOKEN_OUT_REDIR_APPEND)
			check_dup_redir(open(red->filename[i],
					O_WRONLY | O_APPEND | O_CREAT, 0644), red->filename[i], 1);
		else if (red->token == TOKEN_IN_REDIR)
			check_dup_redir(open(red->filename[i],
					O_RDONLY, 0644), red->filename[i], 0);
		else if (red->token == TOKEN_HEREDOC)
			deal_heredoc(red, i);
		i++;
		redir_list = redir_list->next;
	}
	return (redir_exists);
}

int	take_your_builtin(t_main *main, char **args)
{
	if (args == NULL)
		return (0);
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
