/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:52:09 by qsergean          #+#    #+#             */
/*   Updated: 2021/10/12 17:01:41 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
// #include <string.h>

char	*ft_strchr(const char *s, int c)
{
	char	*p;

	p = (char *)s;
	while (*p)
	{
		if (*p == (char)c)
			return (p);
		p++;
	}
	if (*p == '\0' && c == 0)
		return (p);
	return (NULL);
}

// int	main(void)
// {
// 	char str[11]= "biba i boba";

// 	printf("%p\n", ft_strchr(str, '\0'));
// 	printf("%p\n", strchr(str, '\0'));
// }
