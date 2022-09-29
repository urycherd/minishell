/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:06:39 by urycherd          #+#    #+#             */
/*   Updated: 2022/09/29 23:43:45 by urycherd         ###   ########.fr       */
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
		if (ft_change_env(key, path, main))
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
	if (getcwd(cwd, MAX_PATH) == NULL)
		return (1);
	path = ft_strjoin_mod(ft_strjoin(key, "="), cwd);
	if (!(path))
		return (1);
	if (ft_change_env(key, path, main))
		return (1);
	free(path);
	return (0);
}

int	cd_to_arg(t_main *main, char *path)
{
	if (current_pwd_to_key(main, "OLDPWD") && chdir(path) != 0)
		return (1);
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
		if (ft_strcmp(key, str) == 0) //SEGV on unknown address
			return (0);
		envp = envp->next;
		free(key);
	}
	return (1);
}

int	ft_cd(t_main *main, char **args)
{
	// strdup may be needed
	// if (check_key_exist(main, "OLDPWD"))
	// 	ft_lstadd_front(&main->env, ft_lstnew("OLDPWD"));
	// if (check_key_exist(main, "PWD"))
	// {
	// 	ft_lstadd_front(&main->env, ft_lstnew("PWD"));
	// 	current_pwd_to_key(main, "PWD");
	// }
	if (!(args[1]) || ft_strcmp(args[1], "~") == 0
		|| ft_strcmp(args[1], "--") == 0)
		return (cd_to_arg(main, getenv("HOME")));
	if (ft_strcmp(args[1], "-") == 0)
		return (cd_to_arg(main, getenv("OLDPWD")));
	return (cd_to_arg(main, args[1]));
}
