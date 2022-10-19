/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 16:13:59 by qsergean          #+#    #+#             */
/*   Updated: 2022/10/14 18:26:14 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

static const char	*ft_isspace(const char *str)
{
	while (*str)
	{
		if (*str == ' '
			|| *str == '\t'
			|| *str == '\n'
			|| *str == '\v'
			|| *str == '\f'
			|| *str == '\r')
		{
			str++;
			continue ;
		}
		break ;
	}
	return (str);
}

static int	ft_isnum(const char *str, int new)
{
	while (*str)
	{
		if ((*str >= '0') && (*str <= '9'))
		{
			new *= 10;
			new += *str - '0';
			str++;
		}
		else
			break ;
	}
	return (new);
}

int	ft_atoi(const char *str)
{
	int	neg;
	int	new;

	neg = 0;
	new = 0;
	str = ft_isspace(str);
	if (*str == '-')
	{
		neg++;
		str++;
	}
	else if (*str == '+')
		str++;
	new = ft_isnum(str, new);
	if (neg % 2 == 1)
		new = -new;
	return (new);
}
