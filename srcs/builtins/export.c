/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:07:28 by urycherd          #+#    #+#             */
/*   Updated: 2022/09/26 15:46:28 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	print_export(char **massive)
{
	int		y;
	char	*key;

	y = 0;
	while (massive[y])
	{
		ft_putstr_fd("declare -x ", 1);
		key = ft_detect_key(massive[y]);
		if (key)
		{
			ft_putstr_fd(key, 1);
			write(1, "=\"", 2);
			ft_putstr_fd((massive[y] + ft_strlen(key)), 1); // not sure 100% of + strlen
			write(1, "\"\n", 2);
			y++;
			free(key);
		}
	}
}

void	buble_sort(char **arr_str, int size) // потестить сортировку и проверить, что правильно с указателями работаю
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (ft_strcmp(arr_str[j], arr_str[j + 1]) < 0)
			{
				tmp = arr_str[j + 1];
				arr_str[j + 1] = arr_str[j];
				arr_str[j++] = tmp;
			}
		}
		i++;
	}
}

char	**lst_to_arr_str(t_list *env)
{
	char	**arr_str;
	int		i;
	int		size;

	i = 0;
	size = ft_lstsize(env);
	arr_str = (char **)malloc(sizeof(char *) * size);
	while (env->next)
	{
		arr_str[i++] = env->content;
		env = env->next;
	}
	arr_str[i] = env->content;
	buble_sort(arr_str, size);
	return (arr_str);
}

static int	sort_env(t_list *env)
{
	int		i;
	char	**exp;

	i = 0;
	exp = lst_to_arr_str(env);
	print_export(exp);
	while (exp[i])
		free(exp[i++]);
	free(exp);
	return (0);
}

int	ft_export(t_main *main, char **arg)
{
	int	i;

	i = 1;
	if (!arg[1])
		return (sort_env(main->env));
	else
	{
		// while (arg[i])
		// 	if (arg_ex() == 1)
		// 		return (1);
		return (0);
	}
}
