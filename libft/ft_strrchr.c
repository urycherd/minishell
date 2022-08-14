/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:44:15 by qsergean          #+#    #+#             */
/*   Updated: 2021/10/12 17:12:36 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
// #include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*p;
	char	*res;

	p = (char *)s;
	res = NULL;
	while (*p)
	{
		if (*p == (char)c)
			res = p;
		p++;
	}
	if (*p == '\0' && c == 0)
		return (p);
	return (res);
}

// int	main(void)
// {
// 	char str[]= "biba i boba";

// 	printf("%p\n", ft_strrchr(str, 'z'));
// 	printf("%p\n", strrchr(str, 'z'));
// }
