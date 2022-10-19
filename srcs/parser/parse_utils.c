/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:50:01 by qsergean          #+#    #+#             */
/*   Updated: 2022/10/13 23:02:00 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	is_redir(t_list *lexem)
{
	if (((t_lexem *)(lexem->content))->token == TOKEN_OUT_REDIR
		|| ((t_lexem *)(lexem->content))->token == TOKEN_OUT_REDIR_APPEND
		|| ((t_lexem *)(lexem->content))->token == TOKEN_IN_REDIR
		|| ((t_lexem *)(lexem->content))->token == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	get_num_of_args(t_list *lexem)
{
	int		i;
	t_list	*iter;

	i = 0;
	iter = lexem;
	while (iter)
	{
		if (((t_lexem *)(iter->content))->token == TOKEN_WORD)
			i++;
		else if (((t_lexem *)(iter->content))->token == TOKEN_PIPE
			|| is_redir(iter))
			break ;
		iter = iter->next;
	}
	return (i);
}

int	get_num_of_redirs(t_list *lexem)
{
	int		i;
	t_list	*iter;

	i = 0;
	iter = lexem;
	while (iter)
	{
		if (is_redir(iter))
			i++;
		else if (((t_lexem *)(iter->content))->token == TOKEN_PIPE)
			break ;
		iter = iter->next;
	}
	return (i);
}

t_list	*get_lexem_wo_sep(t_list *lexem)
{
	while (lexem)
	{
		if (((t_lexem *)(lexem->content))->token == TOKEN_SEP)
			lexem = lexem->next;
		else
			return (lexem);
	}
	return (lexem);
}
