/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:06:39 by urycherd          #+#    #+#             */
/*   Updated: 2022/09/13 16:22:03 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

// тестить надо + вывод ошибок 

static int	ft_change_env(char *name, char *path, t_list *env)
{
	while (ft_strcmp(name, env->content))
		env = env->next;
	free(env->content);
	env->content = path;
	return (0);
}

static int	go_to(t_list *env, char *name)
{
	char	cwd[MAX_PATH];
	char	*old_path;
	char	*new_path;
	char	*path;
	int		 result;

	// определяем по какому пути пойдем
	path = getenv(name);
	// сохраняем текущую, тк она становится старой
	if (getcwd(cwd, MAX_PATH) == NULL) 
		return (1); 
	if (!(old_path = ft_strjoin("OLDPWD=", cwd)))
		return (1); 
	// переходим на системном уровне в указанную path и задаем ее как новую
	result = chdir(path);
	if (result != 0)
		return (result);
	if (getcwd(cwd, MAX_PATH) == NULL) 
		return (1); 
	if (!(new_path = ft_strjoin("PWD=", cwd)))
		return (1); 
	// сохраняем new_path в env
	if (ft_change_env("PWD=", new_path, env))
		return (1);
	// сохраняем старую в env	
	if (ft_change_env("OLDPWD=", old_path, env))
		return (1);
	free(old_path);
	free(new_path);
	free(path);
	return (0);
}

int	ft_cd(char **args, t_list *env)
{
	int	tmp;

	if (!(args[1]) || ft_strcmp(args[1], "~") == 0|| ft_strcmp(args[1], "--") == 0)
		return go_to(env, "HOME");
	if (ft_strcmp(args[1], "-"))
		return go_to(env, "OLDPWD");
	// update_oldpwd(env);
	tmp = chdir(args[1]);
	// if (tmp != 0)
	// 	error;
	return (tmp);
}
