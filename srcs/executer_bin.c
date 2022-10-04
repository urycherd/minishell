/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_bin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:26:17 by urycherd          #+#    #+#             */
/*   Updated: 2022/10/04 17:16:29 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	print_error_nocmd(char *arg, char *error_name)
{
	ft_putstr_fd("minish: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error_name, 2);
	return (1);
}

static char	*define_path(char **envp)
{
	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	if (*envp == 0)
		return (NULL);
	return (*envp + 5);
}

char	*make_cmd(char **paths, char *incmd)
{
	char	*cmd;

	while (*paths)
	{
		cmd = ft_strjoin_mod(ft_strjoin(*paths, "/"), incmd);
		if (access(cmd, 0) == 0)
			return (cmd);
		free(cmd);
		paths++;
	}
	return (NULL);
}

static void	bin_ex(char **cmd_args, t_ppx *ppx)
{
	ppx->pid = fork();
	if (ppx->pid == -1)
		ft_putstr_fd("Error: fork mistake", 2);
	if (ppx->pid == 0)
	{
		execve(ppx->cmd, cmd_args, ppx->envp);
		ft_putstr_fd("Error: execve mistake", 2);
		exit(1);
	}
}

int	ft_excv(t_main *main, char	**cmd_args)
{
	t_list	*cmd;
	t_list	*env;
	t_ppx	ppx;

	env = main->env;
	cmd = main->commands;
	ppx.envp = lst_to_arr_str(env, ft_lstsize(env));
	ppx.path = define_path(ppx.envp);
	ppx.cmd_paths = ft_split(ppx.path, ':');
	ppx.cmd = make_cmd(ppx.cmd_paths, cmd_args[0]);
	if (!ppx.cmd)
		return (print_error_nocmd(cmd_args[0], "command not found"));
	bin_ex(cmd_args, &ppx);
	waitpid(ppx.pid, NULL, 0);
	return (0);
}
