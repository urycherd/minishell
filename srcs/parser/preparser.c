/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:24:33 by qsergean          #+#    #+#             */
/*   Updated: 2022/10/14 20:51:04 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	join_lexems(t_main **main)
{
	t_list	*lexem;
	t_list	*next;

	lexem = (*main)->lexems;
	if (lexem == NULL)
		return ;
	next = lexem->next;
	while (lexem && next)
	{
		if (((t_lexem *)(lexem->content))->token == TOKEN_WORD
			&& ((t_lexem *)(next->content))->token == TOKEN_WORD)
		{
			((t_lexem *)(lexem->content))->len
				+= ((t_lexem *)(next->content))->len;
			((t_lexem *)(lexem->content))->str
				= ft_strjoin_mod(((t_lexem *)(lexem->content))->str,
					((t_lexem *)(next->content))->str);
			lexem->next = next->next;
			ft_lstdelone(next, free);
			next = lexem->next;
			continue ;
		}
		lexem = lexem->next;
		next = lexem->next;
	}
}

static int	check_lexems_body(t_list **lexem, t_list **next)
{
	while (*lexem && *next)
	{
		if (((((t_lexem *)((*lexem)->content))->token == TOKEN_PIPE
				|| is_redir(*lexem))
			&& (((t_lexem *)((*next)->content))->token == TOKEN_PIPE
			|| is_redir(*next)))
			|| (is_redir(*lexem) && (((t_lexem *)((*next)->content))->token
			!= TOKEN_WORD)))
		{
			ft_putendl_fd("minish: parse error", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		*lexem = (*lexem)->next;
		*next = get_lexem_wo_sep((*lexem)->next);
	}
	return (EXIT_SUCCESS);
}

static int	check_lexems(t_main **main)
{
	t_list	*lexem;
	t_list	*next;
	t_list	*first;

	lexem = (*main)->lexems;
	if (lexem == NULL)
		return (EXIT_FAILURE);
	first = get_lexem_wo_sep(lexem);
	if (((t_lexem *)(first->content))->token == TOKEN_PIPE)
	{
		ft_putendl_fd("minish: parse error", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	next = get_lexem_wo_sep(lexem->next);
	if (check_lexems_body(&lexem, &next) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if ((((t_lexem *)(lexem->content))->token == TOKEN_PIPE
		|| is_redir(lexem)) && next == NULL)
	{
		ft_putendl_fd("minish: parse error", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	preparsing(t_main **main, char *input)
{
	if (lexer(main, input) == EXIT_FAILURE)
	{
		free(input);
		return (EXIT_FAILURE);
	}
	handle_expansions(main);
	join_lexems(main);
	if (check_lexems(main) == EXIT_FAILURE)
	{
		free(input);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
