/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:06:39 by urycherd          #+#    #+#             */
/*   Updated: 2022/09/13 12:48:53 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

// тестить надо + вывод ошибок 

int	ft_change_env(char *name, char *path, t_list *env)
{
	while (ft_strcmp(name, env->content))
		env = env->next;
	free(env->content);
	env->content = path;
	return (0);
}

int	go_to(t_list *env, char *name)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;
	char	*new_pwd;
	char	*path;
	int		 result;

	path = getenv(name);
	// сохраняем текущую, тк она становится старой
	if (getcwd(cwd, PATH_MAX) == NULL) 
		return (1); 
	if (!(old_pwd = ft_strjoin("OLDPWD=", cwd)))
		return (1); 
	// переходим на системном уровне в указанную path и задаем ее как новую
	result = chdir(path);
	if (result != 0)
		return (result);
	if (getcwd(cwd, PATH_MAX) == NULL) 
		return (1); 
	if (!(new_pwd = ft_strjoin("PWD=", cwd)))
		return (1); 
	// сохраняем new_path в env
	if (ft_change_env("PWD=", new_path, env)
		return (1);
	// сохраняем старую в env	
	if (ft_change_env("OLDPWD=", old_path, env)
		return (1);
	free(old_pwd);
	free(new_pwd);
	free(path);
	return (0);
}

int	ft_cd(char **args, t_list *env)
{
	int	tmp;

	if (!(args[1]) || ft_strcmp(args[1], "~") == 0|| ft_strcmp(args[1], "--") == 0)
		return funct(env, "HOME", );
	if (ft_strcmp(args[1], "-")
		return funct(env, "OLDPWD");
	update_oldpwd(env);
	tmp = chdir(args);
	if (tmp != 0)
		error;
	return (tmp);
}
