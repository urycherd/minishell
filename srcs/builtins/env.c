/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:08:08 by urycherd          #+#    #+#             */
/*   Updated: 2022/09/26 15:47:38 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*ft_detect_key(char *str)
{
	char	*key;
	int		i;

	i = 0;
	while (str[i] != '=')
		++i;
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (key == NULL)
		return (NULL);
	i = -1;
	while (str[++i] != '=')
		key[i] = str[i];
	key[i] = '\0';
	return (key);
}

// проверять, что команда без аргументов поступает и выводить ошибку
 
int	ft_env(t_list *env)
{
	if (env)
	{
		while (env->next != NULL)
		{
			ft_putendl_fd(env->content, 1);
			env = env->next;
		}
		ft_putendl_fd(env->content, 1);
	}
	return (0);
}
