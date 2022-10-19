/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:57:41 by qsergean          #+#    #+#             */
/*   Updated: 2022/10/14 19:49:37 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static char	*get_env_name(char *full)
{
	int		len;
	int		i;
	char	*res;

	len = 0;
	while (full && full[len] && full[len] != '=')
		len++;
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < len)
	{
		res[i] = full[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_getenv(t_list *env, char *request)
{
	size_t	len;
	char	*name;

	len = ft_strlen(request);
	while (env)
	{
		name = get_env_name(env->content);
		if (ft_strlen(name) == len)
		{
			if (ft_strncmp(request, name, len) == 0)
			{
				free(name);
				return (env->content + len + 1);
			}
		}
		free(name);
		env = env->next;
	}
	return (NULL);
}

static void	dollar_helper_1(t_main *main, char *input, int *i, char **res)
{
	if (input[*i] == '?')
	{
		*res = ft_itoa(main->exit_f);
		*i += 1;
	}
	else
		*res = "$";
}

static void	dollar_helper_2(t_main *main, char *input, int *i, char **res)
{
	char	*after_dollar;
	int		j;

	after_dollar = (char *)malloc(sizeof(char)
			* (get_word_len(input, *i, ' ', 0) + 2));
	if (after_dollar == NULL)
		exit(EXIT_FAILURE);
	after_dollar[0] = '$';
	j = 1;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\n'
		&& input[*i] != '$' && input[*i] != '\"' && input[*i] != '\''
		&& input[*i] != '<' && input[*i] != '>' && input[*i] != '|')
		after_dollar[j++] = input[(*i)++];
	after_dollar[j] = '\0';
	*res = ft_getenv(main->env, &after_dollar[1]);
	free(after_dollar);
}

void	deal_with_dollar(t_main *main, char *input, int *i, t_lexem **content)
{
	char	*res;

	*i += 1;
	if (!input[*i] || input[*i] == ' ' || input[*i] == '?' || input[*i] == '$')
		dollar_helper_1(main, input, i, &res);
	else
		dollar_helper_2(main, input, i, &res);
	(*content)->token = TOKEN_WORD;
	if (res == NULL)
		(*content)->str = ft_strdup("");
	else
		(*content)->str = ft_strdup(res);
	(*content)->len = ft_strlen((*content)->str);
}
