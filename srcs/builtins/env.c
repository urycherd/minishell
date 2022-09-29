/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:08:08 by urycherd          #+#    #+#             */
/*   Updated: 2022/09/29 21:49:59 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

// проверять, что команда без аргументов поступает и выводить ошибку

int	ft_env(t_list *env)
{
	if (env)
	{
		while (env->next != NULL)
		{
			if (ft_strchr(env->content, '='))
				ft_putendl_fd(env->content, 1);
			env = env->next;
		}
		if (ft_strchr(env->content, '='))
			ft_putendl_fd(env->content, 1);
	}
	return (0);
}
