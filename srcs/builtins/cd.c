/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:06:39 by urycherd          #+#    #+#             */
/*   Updated: 2022/09/09 19:40:38 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args, t_list *env)
{
	int	tmp;

	if (!(args[1]) || ft_strcmp(args[1], "~") == 0|| ft_strcmp(args[1], "--") == 0)
		return funct ;
	if (ft_strcmp(args[1], "-")
		return funct ;
	update_oldpwd(env);
	tmp = chdir(args);
	if (tmp != 0)
		error;
		return (tmp);
}
