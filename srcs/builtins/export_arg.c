/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:18:23 by urycherd          #+#    #+#             */
/*   Updated: 2022/10/03 14:44:55 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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

int	no_key_exp(t_main *main, char *arg)
{
	t_list	*env;
	char	*key;

	env = main->env;
	if (!arg || ft_strchr(arg, '='))
		return (1);
	while (env)
	{
		if (!ft_strcmp(env->content, arg))
			return (0);
		key = ft_detect_key(env->content);
		if (key && !ft_strcmp(key, arg))
		{
			free(key);
			return (0);
		}
		env = env->next;
	}
	ft_lstadd_front(&main->env, ft_lstnew(arg));
	return (0);
}

static int	arg_val_checker(char *arg)
{
	int		i;
	int		ret;
	char	*key;

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

int	rewrite_arg_to_key(t_main *main, char *arg, char *key)
{
	t_list	*env;

	env = main->env;
	while (env)
	{
		if (!ft_strchr(env->content, '=') && !ft_strcmp(env->content, key))
		{
			env->content = arg;
			return (1);
		}	
		env = env->next;
	}
	return (0);
}

int	arg_export(t_main *main, char *arg)
{
	char	*key;
	t_list	*tmp;

	tmp = main->env;
	if (!arg)
		return (1);
	if (arg_val_checker(arg))
		return (1);
	key = ft_detect_key(arg);
	if (key != NULL)
	{
		if (rewrite_key(key, arg, main) || rewrite_arg_to_key(main, arg, key))
		{
			free(key);
			return (0);
		}
		free(key);
		ft_lstadd_front(&main->env, ft_lstnew(arg));
	}
	if (no_key_exp(main, arg))
		return (1);
	return (0);
}
