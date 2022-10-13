/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:44:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/10/13 20:14:16 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	print_error(char *cmd, char *arg, char *error_name)
{
	ft_putstr_fd("minish: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error_name, 2);
	return (1);
}

char	*ft_strjoin_mod(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*res;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		res[i] = s1[i];
		i++;
	}
	while (i - len1 < len2)
	{
		res[i] = s2[i - len1];
		i++;
	}
	res[i] = '\0';
	free(s1);
	return (res);
}

int	change_to_spaces_and_check_quotes(char **str)
{
	int	i;
	int	d_quotes;
	int	s_quotes;

	i = -1;
	d_quotes = 0;
	s_quotes = 0;
	while (str[0][++i])
	{
		if (str[0][i] == '\t' || str[0][i] == '\v'
			|| str[0][i] == '\f' || str[0][i] == '\r')
			str[0][i] = ' ';
		else if (str[0][i] == '\"')
			d_quotes += 1;
		else if (str[0][i] == '\'')
			s_quotes += 1;
	}
	if (d_quotes % 2 != 0 || s_quotes % 2 != 0)
	{
		printf("Number of quotes is not matching!\n");
		return (-1);
	}
	return (i);
}

int	get_word_len(char *str, int i, char c, int flag)
{
	int		res;
	char	extra;

	extra = '\0';
	if (c == ' ' || flag == 1)
		extra = '$';
	res = 0;
	while (str[i + res] && str[i + res] != c
		&& str[i] != '\n' && str[i] != '|' && str[i] != extra)
		res++;
	return (res);
}

void	make_env_list(t_main **main, char **envp)
{
	t_list	*iter;
	int		i;

	(*main)->env = ft_lstnew(envp[0]);
	if ((*main)->env == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (envp[++i])
	{
		iter = ft_lstnew(envp[i]);
		if (iter == NULL)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&(*main)->env, iter);
	}
}

char	*get_env_name(char *full)
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
	// char	*str;
	size_t	len;
	char	*name;

	// if (env)
		// str = (char *)(env->content);
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
	// while (env && str && ft_strnstr(request, str, len))
	// {
	// 	env = env->next;
	// 	if (env)
	// 		str = (char *)(env->content);
	// }
	// if (str == NULL)
	// 	return (NULL);

	// free(name);
	// return (str + len + 1);
}

void	print_lexems(t_main **main)
{
	t_list		*iter;
	t_lexem		*tmp;

	iter = (*main)->lexems;
	printf("\n**************\n");
	printf("{tok, len, str}\n");
	while (iter)
	{
		tmp = iter->content;
		printf("[%u, %d, %s]\n", tmp->token, tmp->len, tmp->str);
		iter = iter->next;
	}
	printf("**************\n\n");
}

void	print_parsed(t_main **main)
{
	t_list		*iter;
	t_list		*i_redir;
	t_command	*cmd;
	int			i;
	int			j;

	printf("**************\n");
	iter = (*main)->commands;
	j = 1;
	while (iter)
	{
		printf("Group number %d:\n", j);
		cmd = iter->content;
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			printf("%s ", (cmd->args)[i]);
			i++;
		}
		i_redir = cmd->redir;
		while (i_redir)
		{
			printf("    //redirect type: %d, filename:",
				((t_redir *)(i_redir->content))->token);
			i = 0;
			while (((t_redir *)(i_redir->content))->filename[i])
			{
				printf(" %s",
					((t_redir *)(i_redir->content))->filename[i]);
				i++;
			}
			i_redir = i_redir->next;
		}
		iter = iter->next;
		j++;
		printf("\n");
	}
	printf("**************\n\n");
}
