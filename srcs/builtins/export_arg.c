/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:18:23 by urycherd          #+#    #+#             */
/*   Updated: 2022/09/28 18:54:58 by urycherd         ###   ########.fr       */
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

int	ft_iscii_arr(char *str)
{
	int		i;

	i = 0;
	while (str[++i])
		if (ft_isascii(str[i]))
			return (1);
	return (0);
}

int	key_val_checker(char *key)
{
	int		i;

	i = 0;
	while (key[++i])
	{
		if (key[i] != '_' && key[i] != '/'
			&& !ft_isalpha(key[i]) && !ft_isdigit(key[i]))
		{
			free(key);
			return (1); //print_error "arg" not a valid identifier
		}
	}
	return (0);
}

static int	arg_val_checker(t_list *env, char *arg)
{
	char	*key;
	int		size;
	int		flag;

	flag = 0;
	size = ft_lstsize(env);
	if (arg[0] != '_' && !ft_isalpha(arg[0]))
		return (1); //print_error "arg" not a valid identifier
	if (ft_iscii_arr(arg))
		return (1); //print_error "arg" not a valid identifier
	if (!(ft_strchr(arg, '=')))
		return (1);
	key = ft_detect_key(arg);
	if (*key)
		if (key_val_checker(key))
			return (1);
	free(key);
	return (flag);
}

int	arg_export(t_list *env, char *arg)
{
	int		i;
	char	*key;
	int		size;

	i = 0;
	size = ft_lstsize(env);
	if (arg_val_checker(arg))
		return (1);
	while (env->next)
	

	//если ключ существует в env - перезаписываем значение
	//иначе добавляем в начало списка
	return (0);
}
