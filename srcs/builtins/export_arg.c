/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:18:23 by urycherd          #+#    #+#             */
/*   Updated: 2022/09/29 21:57:37 by urycherd         ###   ########.fr       */
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
		if (!ft_isascii(str[i]))
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

static int	arg_val_checker(t_main *main, char *arg)
{
	char	*key;
	int		flag;

	flag = 0;
	if (arg[0] != '_' && !ft_isalpha(arg[0]))
		return (1); //print_error "arg" not a valid identifier
	if (ft_iscii_arr(arg))
		return (1); //print_error "arg" not a valid identifier
	if (ft_strchr(arg, '=') == 0)
	{
		if (ft_change_env(arg, arg, main))
			return (0);
		ft_lstadd_front(&main->env, ft_lstnew(arg));
		return (0);
	}
	key = ft_detect_key(arg);
	if (*key)
		if (key_val_checker(key))
			return (1);
	free(key);
	return (flag);
}

int	arg_export(t_main *main, char *arg)
{
	int		i;
	int		size;
	char	*key;
	t_list	*tmp;

	i = 0;
	tmp = main->env;
	size = ft_lstsize(tmp);
	if (arg_val_checker(main, arg))
		return (1);
	key = ft_detect_key(arg);
	if (ft_change_env(key, arg, main))
		return (1);
	ft_lstadd_front(&main->env, ft_lstnew(arg));
	return (0);
}
