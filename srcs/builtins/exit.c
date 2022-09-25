/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:08:05 by urycherd          #+#    #+#             */
/*   Updated: 2022/09/25 18:11:00 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

// ее можно улучшить для этого надо использовать лонг лонг и после этого вписывать в результат от 0 до unsigned max

unsigned int	ft_atou(char *str)
{
	unsigned int	num;
	int				i;
	int				sign;

	i = 0;
	num = 0;
	sign = 1;
	if (str[0] == '-')
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

void	ft_exit(t_main *main, char **arg)
{
	ft_putstr_fd("exit\n", 2);
	if (arg[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	main->exit_f = 1;
	if (arg[1] && ft_strisnum(arg[1]) == 0)
	{
		main->ret = 255;
		ft_putstr_fd("minishell: exit: too many arguments", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else if (arg[1])
		main->ret = ft_atou(num) % 256;
	else
		mini->ret = 0;
}
