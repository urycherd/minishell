/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:07:28 by urycherd          #+#    #+#             */
/*   Updated: 2022/09/27 17:20:29 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	print_export(char **massive, int size)
{
	int		y;
	char	*key;

	y = 0;
	while (y < size)
	{
		ft_putstr_fd("declare -x ", 1);
		key = ft_detect_key(massive[y]);
		if (key)
		{
			ft_putstr_fd(key, 1);
			write(1, "=\"", 2);
			ft_putstr_fd((massive[y] + ft_strlen(key)) + 1, 1);
			write(1, "\"\n", 2);
			free(key);
		}
		y++;
	}
}

static void	buble_sort(char **arr_str, int size)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - 1)
		{
			if (ft_strcmp(arr_str[j], arr_str[j + 1]) > 0)
			{
				tmp = arr_str[j + 1];
				arr_str[j + 1] = arr_str[j];
				arr_str[j] = tmp;
			}
			++j;
		}
		++i;
	}
}

static char	**lst_to_arr_str(t_list *env, int size)
{
	char	**arr_str;
	int		i;

	i = 0;
	arr_str = (char **)malloc(sizeof(char *) * size);
	while (env->next)
	{
		arr_str[i++] = env->content;
		env = env->next;
	}
	arr_str[i] = env->content;
	ft_putnbr_fd(i, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(size, 1);
	write(1, "\n", 1);
	buble_sort(arr_str, size);
	return (arr_str);
}

static int	sort_env(t_list *env)
{
	int		i;
	int		size;
	char	**exp;

	i = -1;
	size = ft_lstsize(env);
	exp = lst_to_arr_str(env, size);
	print_export(exp, size);
	free(exp);
	return (0);
}

int	ft_export(t_main **main, char **arg)
{
	int	i;

	i = 0;
	if (!arg[1])
		return (sort_env((*main)->env));
	else
	{
		while (arg[++i])
			if (arg_export((*main)->env, arg[i]) != 0)
				return (1);
		return (0);
	}
}
