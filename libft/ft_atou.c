/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:19:21 by urycherd          #+#    #+#             */
/*   Updated: 2022/09/22 21:20:24 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static int	ft_pow(int a)
{
	int	i;

	i = 1;
	while (a--)
		i *= 10;
	return (i);
}

static int	ft_int_len_spec(unsigned int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size = 1;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa_spec(unsigned int n)
{
	char	*newnum;
	int		size;
	int		i;

	i = 0;
	size = ft_int_len_spec(n);
	newnum = (char *)malloc(sizeof(char) * size);
	if (!newnum)
		return (0);
	if (n < 0)
	{
		newnum[i] = '-';
		i++;
	}
	while (i < size)
	{
		if (n < 0)
			newnum[i] = -(n / ft_pow(size - i - 1) % 10) + '0';
		else
			newnum[i] = (n / ft_pow(size - i - 1) % 10) + '0';
		i++;
	}
	newnum[i] = '\0';
	return (newnum);
}