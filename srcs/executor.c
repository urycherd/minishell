/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:23:36 by urycherd          #+#    #+#             */
/*   Updated: 2022/10/05 20:05:17 by urycherd         ###   ########.fr       */
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

// int	ft_pipex(t_main *main, char **args)
// {
// 	t_cmd	*tmp;
// 	t_cmd	*prev;
// 	int		fd1[2];
// 	int		fd_tmp;
// 	// t_list	*cmd;
// 	// 	t_ppx	ppx;

// 	// cmd = main->commands;
// // 	if (pipe(ppx->fd) == -1)
// // 		ft_error("Error: pipe problems");
// // 	while (cmd)
// // 	{
// // 		dup2(lol->fd[1], 1); // меняем запись вместо stdout (вывод) в pipe
// // 		close(lol->fd[0]); // закрываю на чтение
// // 		// dup2(lol->file1, 0); // меняем чтение из фйал вместо stdin (ввод)


// // 		// dup2(lol->fd[0], 0); // меняем чтение вместо stdin (ввод) в pipe
// // 		// close(lol->fd[1]); // закрываю на запись
// // 		// dup2(lol->file2, 1); // меняем запись в фйал вместо stdout (вывод)
// // 		ft_excv(main, args);
// // 		cmd = cmd->next;
// // 	}

// 	tmp = main->commands;
// 	prev = NULL;
// 	while (tmp != NULL)
// 	{
// 		if (pipe(fd1) == -1)
// 			ft_error("Error: pipe problems");
// 		if (prev == NULL)
// 			exec_first_cmd(*env, tmp, fd1);
// 		else if (((t_list *)tmp)->next == NULL)
// 			exec_last_cmd(*env, tmp);
// 		else
// 			exec_middle_cmd(*env, tmp);
// 		prev = tmp;
// 		tmp = tmp->next;
// 	}

// 	return (0);
// }

int	executor(t_main *main)
{
	char	**args;
	t_list	*cmd;

	args = ((t_command *)(main->commands->content))->args;
	cmd = main->commands;
	// check if redirect
	// 		dup2
	if (cmd && !cmd->next) // for 1 param
	{
		if (take_your_builtin(main) >= 0)
			return (0);
		if (ft_excv(main, args))
			return (0);
	}
	// else
	// 	if (ft_pipex())
	// 		return (1);
	return (0);
}
