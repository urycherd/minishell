/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:08:11 by urycherd          #+#    #+#             */
/*   Updated: 2022/10/05 20:05:42 by urycherd         ###   ########.fr       */
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

int	rewrite_key(char *key, char *path, t_main *main)
{
	t_list	*tmp;
	int		ln;
	char	*c;

	tmp = main->env;
	while (tmp)
	{
		ln = ft_strlen(key);
		c = tmp->content;
		if (ft_strncmp(tmp->content, key, ln) == 0 && c[ln] == '=')
		{
			tmp->content = path;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static size_t	key_size(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static int	unsetting(t_main **main, char *arg, t_list *env)
{
	if (ft_strncmp(arg, env->content, key_size(env->content)) == 0)
	{
		if (env->next)
			(*main)->env = env->next;
		free(env);
		return (1);
	}
	while (env && env->next)
	{
		if (ft_strncmp(arg, env->next->content, \
		key_size(env->next->content)) == 0)
		{
			env->next = env->next->next;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	ft_unset(t_main **main, char **arg)
{
	int		i;

	i = 0;
	while (arg[++i])
	{
		unsetting(main, arg[i], (*main)->env);
	}
	return (0);
}
