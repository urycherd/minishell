/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:18:23 by urycherd          #+#    #+#             */
/*   Updated: 2022/10/03 12:23:05 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*ft_detect_key(char *str)
{
	char	*key;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		++i;
	if (str[i] != '=')
		return (NULL);
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = -1;
	while (str[++i] && str[i] != '=')
		key[i] = str[i];
	key[i] = '\0';
	return (key);
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
			print_error("export: ", key, "not a valid identifier");
			free(key);
			return (1);
		}
	}
	return (0);
}


// if (!ft_strchr(arg, '='))
// 	{
// 		while (env)
// 		{
// 			if (!ft_strchr(env->content, '='))
// 				key = strdup(env->content);
// 			else
// 				key = ft_detect_key(env->content);
// 			if (key != NULL)
// 			{
// 				if (!ft_strcmp(arg, key)) //  тут проблема Проверка есть ли ключ! c именем параметра уже в списках (если есть - выходим 1)
// 				{
// 					free(key);
// 					return (1);
// 				}	
// 				free(key);
// 				env = env->content;
// 			}
// 		}
// 		ft_lstadd_front(&main->env, ft_lstnew(arg));
// 		return (0);
// 	}

static int	arg_val_checker(t_main *main, char *arg)
{
	int		i;
	int		ret;
	char	*key;
	t_list	*env;

	env = main->env;
	ret = 0;
	i = 0;
	if (arg[0] != '_' && !ft_isalpha(arg[0]))
		return (print_error("export", arg, "not a valid identifier"));
	while (arg[++i])
		if (!ft_isascii(arg[i]))
			return (print_error("export", arg, "not a valid identifier"));
	key = ft_detect_key(arg);
	if (key != NULL)
	{
		ret = key_val_checker(key);
		free(key);
	}
	return (ret);
}

int	arg_export(t_main *main, char *arg)
{
	int		i;
	char	*key;
	t_list	*tmp;

	i = 0;
	tmp = main->env;
	if (!arg)
		return (1);
	if (arg_val_checker(main, arg)) // только проверить поступающие значения
		return (1);
	key = ft_detect_key(arg);
	if (key != NULL)
	{
		if (ft_rewrite_env(key, arg, main)) // если перезапись значения ключа происходит ...
		{
			free(key);
			return (0);
		}
		ft_lstadd_front(&main->env, ft_lstnew(arg));
		free(key);
	}
	return (0);
}
