/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:08:08 by urycherd          #+#    #+#             */
/*   Updated: 2022/09/09 17:07:19 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_list *env)
{
	if (env)
	{
		while (env->next != NULL)
		{
			ft_putstr_fd(env->content, 1);
			write(1, '\n', 1)
			env = env->next;
		}
		ft_putstr_fd(env->content, 1);
	}
	return (0);
}
