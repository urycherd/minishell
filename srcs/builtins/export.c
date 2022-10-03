/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:07:28 by urycherd          #+#    #+#             */
/*   Updated: 2022/10/03 11:35:00 by urycherd         ###   ########.fr       */
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
		if (!ft_strchr(massive[y], '='))
			key = strdup(massive[y]);
		else
			key = ft_detect_key(massive[y]);
		if (key != NULL)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(key, 1);
			if (ft_strchr(massive[y], '='))
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd((massive[y] + ft_strlen(key)) + 1, 1);
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
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

char	**lst_to_arr_str(t_list *env, int size)
{
	char	**arr_str;
	int		i;

	i = 0;
	arr_str = (char **)malloc(sizeof(char *) * size);
	while (env)
	{
		arr_str[i++] = env->content;
		env = env->next;
	}
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
	if (!exp)
		return (1);
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
			arg_export(*main, arg[i]);
		return (0);
	}
}
