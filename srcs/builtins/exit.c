/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:08:05 by urycherd          #+#    #+#             */
/*   Updated: 2022/10/14 20:23:09 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

unsigned int	ft_atou(char *str)
{
	unsigned int	num;
	int				i;
	int				sign;

	i = 0;
	num = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (sign < 0)
		num = 4294967296 - num;
	return (num);
}

static int	ft_strisnum(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_main *main, char **arg)
{
	ft_putendl_fd(arg[0], 2);
	if (arg[1] && arg[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	main->exit_f = 1;
	if (arg[1] && ft_strisnum(arg[1]) == 0)
	{
		main->ret = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (arg[1])
		main->ret = ft_atou(arg[1]) % 256;
	else
		main->ret = 0;
	return (0);
}
