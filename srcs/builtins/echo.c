/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:06:13 by urycherd          #+#    #+#             */
/*   Updated: 2022/10/02 16:51:43 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	all_one_elem(char *str, char c)
{
	int	i;

	i = 0;
	if (!str[i] || !c)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			++i;
		else
			return (0);
	}
	return (1);
}

int	ft_echo(char **args)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (args[i] && args[1][0] == '-')
	{
		if (all_one_elem(args[1] + 1, 'n'))
		{
			n_flag = 1;
			i++;
		}
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] && args[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (n_flag == 0)
		write(1, "\n", 1);
	return (0);
}
