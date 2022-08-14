/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:32:59 by qsergean          #+#    #+#             */
/*   Updated: 2021/10/26 19:42:17 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
// #include <string.h>

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

// int	main(void)
// {
// 	char	*str1 = (void *)0;
// 	char	str2[] = "fake";

// 	printf("%s\n", ft_strnstr(str1, str2, 3));
// 	// printf("%s\n", strnstr(str1, str2, 3));
// }
