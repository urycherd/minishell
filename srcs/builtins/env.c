/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:08:08 by urycherd          #+#    #+#             */
/*   Updated: 2022/10/03 21:54:26 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_env(t_list *env, char **arg)
{
	if (arg[1])
		return (print_error("env", arg[1], "No such file or directory"));
	while (env)
	{
		if (ft_strchr(env->content, '='))
			ft_putendl_fd(env->content, 1);
		env = env->next;
	}
	return (0);
}
