/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:04:23 by qsergean          #+#    #+#             */
/*   Updated: 2021/10/21 17:49:29 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/errno.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	res = (void *)malloc(count * size);
	if (res == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	res = ft_bzero(res, count * size);
	return (res);
}
