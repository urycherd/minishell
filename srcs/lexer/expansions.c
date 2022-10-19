/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:56:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/10/13 22:58:28 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	ft_lstadd_after(t_list **node, t_list **new)
{
	t_list	*tmp;

	if (*node == NULL || *new == NULL)
		return ;
	tmp = (*node)->next;
	(*node)->next = *new;
	(*new)->next = tmp;
}

static t_list	*ft_lstdel_smart(t_list **list, t_list *node)
{
	t_list	*iter;
	t_list	*tmp;

	iter = (*list);
	if (iter == node)
	{
		tmp = *list;
		*list = (*list)->next;
		ft_lstdelone(tmp, free);
		return (*list);
	}
	else
	{
		while (iter)
		{
			if (iter->next == node)
				break ;
			iter = iter->next;
		}
		iter->next = node->next;
		ft_lstdelone(node, free);
		return (iter);
	}
}

static void	deal_with_word_light(char *input, int *i, t_lexem **content)
{
	int	j;

	(*content)->len = get_word_len(input, *i, ' ', 0);
	(*content)->str = (char *)malloc(sizeof(char)
			* (get_word_len(input, *i, '\0', 1) + 1));
	if ((*content)->str == NULL)
		exit(EXIT_FAILURE);
	j = 0;
	while (input[*i] != '\n' && input[*i] != '\0'
		&& input[*i] != '$')
	{
		(*content)->str[j] = input[*i];
		j++;
		*i += 1;
	}
	(*content)->str[j] = '\0';
	(*content)->token = TOKEN_WORD;
}

void	handle_expansions_body(t_main *main, char *str,
	t_lexem **content, t_list **save)
{
	int		i;
	t_list	*new_lexem;

	i = 0;
	while (str && str[i])
	{
		*content = (t_lexem *)malloc(sizeof(t_lexem));
		if (*content == NULL)
			exit(EXIT_FAILURE);
		if (str[i] == '$')
			deal_with_dollar(main, str, &i, content);
		else if (str && str[i])
			deal_with_word_light(str, &i, content);
		new_lexem = ft_lstnew(*content);
		if (new_lexem == NULL)
			exit(EXIT_FAILURE);
		ft_lstadd_after(save, &new_lexem);
		*save = (*save)->next;
	}
}

void	handle_expansions(t_main **main)
{
	t_list	*lexem;
	t_list	*save;
	t_lexem	*content;
	char	*str;

	lexem = (*main)->lexems;
	while (lexem)
	{
		if (((t_lexem *)(lexem->content))->token == TOKEN_DQUOTE)
		{
			save = lexem;
			str = ((t_lexem *)(lexem->content))->str;
			handle_expansions_body(*main, str, &content, &save);
			ft_lstdel_smart(&(*main)->lexems, lexem);
			lexem = save;
		}
		lexem = lexem->next;
	}
}
