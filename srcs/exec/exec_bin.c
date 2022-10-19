/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_bin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:26:17 by urycherd          #+#    #+#             */
/*   Updated: 2022/10/13 23:05:28 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	print_error_nocmd(char *arg, char *error_name)
{
	ft_putstr_fd("minish: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error_name, 2);
	return (1);
}

static char	*define_path(t_list *envp)
{
	while (envp && ft_strncmp("PATH=", (char *)(envp->content), 5))
		envp = envp->next;
	if (!envp)
		return (NULL);
	return ((char *)(envp->content) + 5);
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
		print_error_nocmd(cmd_args[0], "command not found");
		exit(1);
	}
}

int	ft_excv(t_main *main, char	**cmd_args, t_list	*next)
{
	t_list	*env;
	t_ppx	exv;

	env = main->env;
	exv.envp = lst_to_arr_str(env, ft_lstsize(env));
	if (cmd_args == NULL)
		return (0);
	if (!ft_strncmp(cmd_args[0], "./", 2) || !ft_strncmp(cmd_args[0], "../", 3)
		|| !ft_strncmp(cmd_args[0], "/bin/", 5) || cmd_args[0][0] == '/')
		exv.cmd = ft_strdup(cmd_args[0]);
	else
	{
		exv.path = define_path(env);
		if (!exv.path)
			return (print_error_nocmd(cmd_args[0],
					"No such file or directory"));
		exv.cmd_paths = ft_split(exv.path, ':');
		exv.cmd = make_cmd(exv.cmd_paths, cmd_args[0]);
	}	
	if (!exv.cmd)
		return (print_error_nocmd(cmd_args[0], "command not found"));
	bin_ex(cmd_args, &exv);
	if (next == NULL)
		waitpid(exv.pid1, NULL, 0);
	return (0);
}
