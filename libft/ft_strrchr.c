/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:44:15 by qsergean          #+#    #+#             */
/*   Updated: 2022/09/27 14:44:09 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

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
