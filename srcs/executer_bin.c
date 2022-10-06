/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_bin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:26:17 by urycherd          #+#    #+#             */
/*   Updated: 2022/10/05 13:41:09 by urycherd         ###   ########.fr       */
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

static void	bin_ex(char **cmd_args, t_ppx *exv)
{
	exv->pid1 = fork();
	if (exv->pid1 == -1)
		ft_putstr_fd("Error: fork mistake", 2);
	if (exv->pid1 == 0)
	{
		execve(exv->cmd, cmd_args, exv->envp);
		ft_putstr_fd("Error: execve mistake", 2);
		exit(1);
	}
}

int	ft_excv(t_main *main, char	**cmd_args)
{
	t_list	*cmd;
	t_list	*env;
	t_ppx	exv;

	env = main->env;
	cmd = main->commands;
	exv.envp = lst_to_arr_str(env, ft_lstsize(env));
	exv.path = define_path(exv.envp);
	exv.cmd_paths = ft_split(exv.path, ':');
	exv.cmd = make_cmd(exv.cmd_paths, cmd_args[0]);
	ft_putendl_fd(cmd_args[0], 2);
	// ft_putendl_fd(, 2);
	// ft_putendl_fd(, 2);
	if (!exv.cmd)
		return (print_error_nocmd(cmd_args[0], "command not found"));
	bin_ex(cmd_args, &exv);
	waitpid(exv.pid1, NULL, 0);
	return (0);
}
