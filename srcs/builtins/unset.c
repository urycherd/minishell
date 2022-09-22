/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:08:11 by urycherd          #+#    #+#             */
/*   Updated: 2022/09/22 17:49:39 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	env_size(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static int	node_switch(char **env)
{
	s_list	tmp;

	tmp = (*env)->next->next;
	ft_lstdelone((*env)->next, free);
	(*env)->next = tmp;
}

int	ft_unset(char **args, s_main *main)
{
	s_list	env;

	env = main->env;
	if (!args[1])
		return (0);
	if (ft_strncmp(args[1], env->content, env_size(env->content)) == 0)
	{
		if (env->next)
			main->env = env->next;
		ft_lstdelone(env, free);
		return (0);
	}
	while (env && env->next)
	{
		if (ft_strncmp(args[1], env->next->content, \
		env_size(env->next->content)) == 0)
		{
			node_switch(*env);
			return (0);
		}
		env = env->next;
	}
	return (0);
}
