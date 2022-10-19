/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:51:06 by qsergean          #+#    #+#             */
/*   Updated: 2022/10/14 18:26:14 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

static long int	ft_abs(long int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

static int	ft_numlen(int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		len += 1;
		n *= -1;
	}
	while (n / 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;
	int		sign;

	if (n < 0)
		sign = -1;
	else
		sign = 1;
	i = ft_numlen(n);
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (res == NULL)
		return (NULL);
	res[i--] = '\0';
	while (i >= 0)
	{
		res[i] = '0' + ft_abs(n % 10);
		n = ft_abs(n / 10);
		i--;
	}
	if (sign == -1)
		res[0] = '-';
	return (res);
}
