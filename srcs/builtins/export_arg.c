/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:18:23 by urycherd          #+#    #+#             */
/*   Updated: 2022/09/27 17:59:58 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*ft_detect_key(char *str)
{
	char	*key;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		++i;
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (key == NULL)
		return (NULL);
	i = -1;
	while (str[++i] && str[i] != '=')
		key[i] = str[i];
	key[i] = '\0';
	return (key);
}

static int	key_checker(char *arg)
{
	int		i;
	char	*key;
	int		size;

	i = 0;
	size = ft_lstsize(env);
	if (arg[0] != '_' && !ft_isalpha(arg[0]))
		return (1);
	if (!(ft_strchr(arg, '=')))
		return (1);
	key = ft_detect_key(arg);
	while (key[++i])
	{
		if (key[i] != '_' && key[i] != '/'
			&& !ft_isalpha(key[i]) && !ft_isdigit(key[i]))
		{
			free(key);
			return (1);
		}
	}
	free(key);
	return (0);
}

int	arg_export(t_list *env, char *arg)
{
	int		i;
	char	*key;
	int		size;

	i = 0;
	size = ft_lstsize(env);
	if (key_checker(arg))
		return (1);
	
	//если ключ существует в env - перезаписываем значение
	//иначе добавляем в начало списка
	return (0);
}
