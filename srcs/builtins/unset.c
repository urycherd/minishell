/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:08:11 by urycherd          #+#    #+#             */
/*   Updated: 2022/10/02 20:07:10 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_rewrite_env(char *key, char *path, t_main *main)
{
	t_list	*tmp;
	int		ln;

	tmp = main->env;
	while (tmp)
	{
		ln = ft_strlen(key);
		if (ft_strncmp(tmp->content, key, ln) == 0)
		{
			tmp->content = path;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static size_t	key_size(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

// static void	node_switch(t_list **env)
// {
// 	// t_list	*tmp;

// 	// tmp = (*env)->next->next;
// 	// // free(env);
// 	// // ft_lstdelone((*env)->next, free); // attempting free on address which was not malloc()-ed:
// 	// (*env)->next = tmp;
// }

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
			free(env);
			// ft_lstdelone(env, free); // attempting free on address which was not malloc()-ed:
			return ;
		}
		while (env && env->next)
		{
			if (ft_strncmp(arg[i], env->next->content, \
			key_size(env->next->content)) == 0)
			{
				// node_switch(&env);
				env->next = env->next->next; // почему не надо фришить узел??
				return ;
			}
			env = env->next;
		}
	}
}
