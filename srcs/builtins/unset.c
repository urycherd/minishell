/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:08:11 by urycherd          #+#    #+#             */
/*   Updated: 2022/09/29 15:35:18 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static size_t	key_size(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void	node_switch(t_list **env)
{
	t_list	*tmp;

	tmp = (*env)->next->next;
	ft_lstdelone((*env)->next, free);
	(*env)->next = tmp;
}

void	ft_unset(t_main **main, char **arg)
{
	t_list	*env;
	int		i;

	i = 0;
	env = (*main)->env;
	while (arg[++i])
	{
		if (ft_strncmp(arg[i], env->content, key_size(env->content)) == 0)
		{
			if (env->next)
				(*main)->env = env->next;
			ft_lstdelone(env, free);
			return ;
		}
		while (env && env->next)
		{
			if (ft_strncmp(arg[i], env->next->content, \
			key_size(env->next->content)) == 0)
			{
				node_switch(&env);
				return ;
			}
			env = env->next;
		}
	}
}
