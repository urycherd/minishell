/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:06:39 by urycherd          #+#    #+#             */
/*   Updated: 2022/10/04 17:41:53 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	make_new_key(t_main *main, char *key, char	*path)
{
	if (ft_strcmp(key, "OLDPWD") == 0)
		ft_putendl_fd("bash: cd: OLDPWD not set", 2);
	else if (ft_strcmp(key, "PWD") == 0)
	{
		ft_lstadd_front(&main->env, ft_lstnew(key));
		if (rewrite_key(key, path, main))
			return (1);
	}
	return (0);
}

int	current_pwd_to_key(t_main *main, char *key)
{
	char	*path;
	char	cwd[MAX_PATH];
	t_list	*tmp;

	tmp = main->env;
	if (!key || getcwd(cwd, MAX_PATH) == NULL)
		return (1);
	path = ft_strjoin_mod(ft_strjoin(key, "="), cwd);
	if (!(path))
		return (1);
	if (rewrite_key(key, path, main))
		return (1);
	free(path);
	return (0);
}

int	cd_to_arg(t_main *main, char *path)
{
	if (!current_pwd_to_key(main, "OLDPWD"))
		return (1);
	if (chdir(path) == -1)
		return (print_error("cd", path, "No such file or directory"));
	if (current_pwd_to_key(main, "PWD"))
		return (1);
	return (0);
}

int	check_key_exist(t_main *main, char *str)
{
	t_list	*envp;
	char	*key;

	envp = main->env;
	while (envp)
	{
		key = ft_detect_key(envp->content);
		if (key != NULL)
		{
			if (ft_strcmp(key, str) == 0)
			{
				free(key);
				return (0);
			}
			free(key);
		}
		envp = envp->next;
	}
	return (1);
}

int	ft_cd(t_main *main, char **args)
{
	if (check_key_exist(main, "OLDPWD"))
		ft_lstadd_front(&main->env, ft_lstnew("OLDPWD="));
	if (check_key_exist(main, "PWD"))
	{
		ft_lstadd_front(&main->env, ft_lstnew("PWD="));
		current_pwd_to_key(main, "PWD");
	}
	if (!(args[1]) || ft_strcmp(args[1], "~") == 0
		|| ft_strcmp(args[1], "--") == 0)
		return (cd_to_arg(main, getenv("HOME")));
	if (ft_strcmp(args[1], "-") == 0)
		return (cd_to_arg(main, getenv("OLDPWD")));
	return (cd_to_arg(main, args[1]));
	return (0);
}

// bash: cd: arg: error_msg