/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:07:28 by urycherd          #+#    #+#             */
/*   Updated: 2022/09/25 18:08:47 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**ft_detect_key(char *str)
{
	char	*key;
	int		i;

	i = 0;
	while (str[i] != '=')
		++i;
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (key == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '=')
		key = str[i++];
	key[i] = '\0';
	return (key);
}

void	print_dar(char **massive)
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
			ft_putstr_fd(detect_key(massive[y]), 1);
			write(1, "=\"", 2);
			ft_putstr_fd((massive[y] + ft_strlen(key)), 1);
			write(1, "\"\n", 2);
			y++;
			free(key);
		}
	}
}

char	**lst_to_dar(t_list *env)
{
	char	**dar;
	int		i;
	int		size;

	i = 0;
	size = ft_lstsize(env);
	dar = (char **)malloc(sizeof(char *) * size);
	while (env->next)
	{
		dar[i++] = env->content;
		env = env->next;
	}
	dar[i] = env->content;
	return (dar);
}

static int	sort_env(t_list *env)
{
	char	**exp;
	char	*tmp;
	int		size;
	int		i;
	int		j;

	i = 0;
	size = ft_lstsize(env);
	exp = lst_to_dar(env);
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (ft_strcmp(exp[j], exp[j + 1]) < 0)
			{
				tmp = exp[j + 1];
				exp[j + 1] = exp[j];
				exp[j++] = tmp;
			}
		}
		i++;
	}
	print_dar(exp);
	// free(exp);
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
		while (arg[i])
			if (arg_ex() == 1)
				return (1);
		return (0);
	}
}
