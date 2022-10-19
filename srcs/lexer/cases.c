/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:06:02 by qsergean          #+#    #+#             */
/*   Updated: 2022/10/13 22:16:14 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	deal_with_redir_1(char *input, int *i, t_lexem **content)
{
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			(*content)->str = ">>";
			(*content)->token = TOKEN_OUT_REDIR_APPEND;
			(*content)->len = 2;
		}
		else
		{
			(*content)->str = ">";
			(*content)->token = TOKEN_OUT_REDIR;
			(*content)->len = 1;
		}
	}
}

void	deal_with_redir(char *input, int *i, t_lexem **content)
{
	deal_with_redir_1(input, i, content);
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			(*content)->str = "<<";
			(*content)->token = TOKEN_HEREDOC;
			(*content)->len = 2;
		}
		else
		{
			(*content)->str = "<";
			(*content)->token = TOKEN_IN_REDIR;
			(*content)->len = 1;
		}
	}
	*i += (*content)->len;
}

void	spc_nwln_pipe(char *input, int *i, t_lexem **content)
{
	if (input[*i] == ' ')
	{
		(*content)->str = " ";
		(*content)->token = TOKEN_SEP;
	}
	else if (input[*i] == '|')
	{
		(*content)->str = "|";
		(*content)->token = TOKEN_PIPE;
	}
	else if (input[*i] == '\n')
	{
		(*content)->str = " ";
		(*content)->token = TOKEN_NEWLINE;
	}
	(*content)->len = 1;
	*i += 1;
}

void	deal_with_quotes(char *input, int *i, t_lexem **content)
{
	int		j;

	if ((*content)->len == 0)
	{
		free(*content);
		*i += 2;
		return ;
	}
	(*content)->len = get_word_len(input, *i + 1, input[*i], 0);
	if (input[*i] == '\"')
		(*content)->token = TOKEN_DQUOTE;
	else
		(*content)->token = TOKEN_WORD;
	(*content)->str = (char *)malloc(sizeof(char) * ((*content)->len + 1));
	if ((*content)->str == NULL)
		exit(EXIT_FAILURE);
	j = 0;
	while (input[*i + j + 1] && input[*i + j + 1] != input[*i])
	{
		(*content)->str[j] = input[*i + j + 1];
		j++;
	}
	(*content)->str[j] = '\0';
	*i += (*content)->len + 2;
}

void	deal_with_word(char *input, int *i, t_lexem **content)
{
	int	j;

	(*content)->len = get_word_len(input, *i, ' ', 0);
	(*content)->str = (char *)malloc(sizeof(char)
			* (get_word_len(input, *i, ' ', 0) + 1));
	if ((*content)->str == NULL)
		exit(EXIT_FAILURE);
	j = 0;
	while (input[*i] != ' ' && input[*i] != '\n'
		&& input[*i] != '\0' && input[*i] != '$'
		&& input[*i] != '\'' && input[*i] != '\"'
		&& input[*i] != '|' && input[*i] != '>'
		&& input[*i] != '<')
	{
		(*content)->str[j] = input[*i];
		j++;
		*i += 1;
	}
	(*content)->str[j] = '\0';
	(*content)->token = TOKEN_WORD;
}
