/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:35:46 by qsergean          #+#    #+#             */
/*   Updated: 2021/10/26 20:00:47 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

static char	**ft_count_words(char const *str, char c, size_t *words)
{
	size_t		i;
	char		**res;

	i = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] == '\0')
			break ;
		while (str[i] != c && str[i] != '\0')
			i++;
		*words += 1;
	}
	res = (char **)malloc(sizeof(char *) * (*words + 1));
	if (res == NULL)
		return (NULL);
	return (res);
}

static char	**ft_count_letters(char const *str, char c,
	size_t words, char **res)
{
	size_t	i;
	int		num;
	size_t	letters;

	num = 0;
	i = 0;
	while (num < (int)words && str[i])
	{
		letters = 0;
		while (str[i] == c)
			i++;
		while (str[i] != c && str[i++])
			letters++;
		res[num] = (char *)malloc(sizeof(char) * (letters + 1));
		if (res[num] == NULL)
		{
			while (num-- > -1)
				free(res[num]);
			free(res);
			return (NULL);
		}
		num++;
	}
	res[num] = NULL;
	return (res);
}

static char	**ft_fill(char const *str, char c, size_t words, char **res)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < words)
	{
		while (*str == c)
			str++;
		j = 0;
		while (*str != c && *str)
		{
			res[i][j] = *str;
			j++;
			str++;
		}
		res[i][j] = '\0';
		if (!*str)
			break ;
		i++;
		str++;
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	words;

	if (s == NULL)
		return (NULL);
	words = 0;
	res = ft_count_words(s, c, &words);
	if (res == NULL)
		return (NULL);
	res = ft_count_letters(s, c, words, res);
	if (res == NULL)
		return (NULL);
	res = ft_fill(s, c, words, res);
	return (res);
}

// int	main(void)
// {
// 	char	*s = "";
// 	char	c = ' ';
// 	char	**res;
// 	int		i;

// 	res = ft_split(s, c);
// 	i = 0;
// 	while (res[i] != NULL)
// 	{
// 		printf("%s\n", res[i]);
// 		i++;
// 	}
// }
