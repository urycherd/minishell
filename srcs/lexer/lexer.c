/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:42:06 by qsergean          #+#    #+#             */
/*   Updated: 2022/10/13 22:06:43 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	lexer_body(t_main *main, char *input, t_lexem **content, int *i)
{
	if (input[*i] == ' ' || input[*i] == '|' || input[*i] == '\n')
		spc_nwln_pipe(input, i, content);
	else if (input[*i] == '>' || input[*i] == '<')
		deal_with_redir(input, i, content);
	else if (input[*i] == '\"' || input[*i] == '\'')
		deal_with_quotes(input, i, content);
	else if (input[*i] == '$')
		deal_with_dollar(main, input, i, content);
	else
		deal_with_word(input, i, content);
}

int	lexer(t_main **main, char *input)
{
	t_list	*new_lexem;
	t_lexem	*content;
	int		i;

	add_history(input);
	if (change_to_spaces_and_check_quotes(&input) < 0)
		return (EXIT_FAILURE);
	(*main)->lexems = NULL;
	i = 0;
	while (input[i])
	{
		content = (t_lexem *)malloc(sizeof(t_lexem));
		if (content == NULL)
			exit(EXIT_FAILURE);
		lexer_body(*main, input, &content, &i);
		if (content->len == 0)
			continue ;
		new_lexem = ft_lstnew((void *)content);
		if (new_lexem == NULL)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&(*main)->lexems, new_lexem);
	}
	return (EXIT_SUCCESS);
}
