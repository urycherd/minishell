/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:08:05 by urycherd          #+#    #+#             */
/*   Updated: 2022/09/22 21:59:21 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strisnum(char *str)
{
	int	i;

	i = 0;
	while (str)
	{

	}
}

void	ft_exit(t_main *main, char **arg)
{
	ft_putstr_fd("exit ", 2);
	// if more then 1 arg - error
	if (cmd[2])
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	else if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	{
		main->exit_f = 1;
		main->ret = ft_itou(num) % 256;
	}
	// if arg not num - error
	else if ()
	{}
	else if ()
	{}
	// if num and shorter then 10 symbles - i'm takeing module of this num (возвращает в процесс n % 256)
}
