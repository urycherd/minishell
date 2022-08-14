/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:31:17 by qsergean          #+#    #+#             */
/*   Updated: 2021/10/12 20:06:09 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
// #include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*p;

	p = (char *)s;
	while (n--)
	{
		if (*p == (char)c)
			return (p);
		p++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	str[] = "biba i boba";

// 	printf("%p\n", ft_memchr(str, '\0', 20));
// 	printf("%p\n", memchr(str, '\0', 20));
// }
