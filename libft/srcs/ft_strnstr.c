/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:32:59 by qsergean          #+#    #+#             */
/*   Updated: 2022/10/14 18:26:14 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	ndllen;

	ndllen = ft_strlen(needle);
	if (!ndllen)
		return ((char *)haystack);
	while (((len >= ndllen) && *haystack) || haystack == NULL)
	{	
		len--;
		if (!ft_memcmp(haystack, needle, ndllen))
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
