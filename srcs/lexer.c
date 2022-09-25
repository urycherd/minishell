/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:42:06 by qsergean          #+#    #+#             */
/*   Updated: 2022/09/25 18:55:21 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	deal_with_redir(char *input, int i, t_lexem **content)
{
	if (input[i] == '>')
	{
		if (input[i + 1] == '>')
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
	else if (input[i] == '<')
	{
		if (input[i + 1] == '<')
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
}

static void	spc_nwln_pipe(char *input, int i, t_lexem **content)
{
	if (input[i] == ' ')
	{
		(*content)->str = " ";
		(*content)->token = TOKEN_SEP;
		(*content)->len = 1;
	}
	else if (input[i] == '|')
	{
		(*content)->str = "|";
		(*content)->token = TOKEN_PIPE;
		(*content)->len = 1;
	}
	else if (input[i] == '\n')
	{
		(*content)->str = " ";
		(*content)->token = TOKEN_NEWLINE;
		(*content)->len = 1;
	}
}

static void	deal_with_quotes(char *input, int *i, t_lexem **content)
{
	int		j;
	char	c;

	c = input[*i];
	(*content)->len = get_word_len(input, *i + 1, c);
	if ((*content)->len == 0)
	{
		free(*content);
		*i += 2;
		return ;
	}
	if (c == '\"')
		(*content)->token = TOKEN_DQUOTE;
	else
		(*content)->token = TOKEN_WORD;
	(*content)->str = (char *)malloc(sizeof(char) * ((*content)->len + 1));
	if ((*content)->str == NULL)
		exit(EXIT_FAILURE);
	j = 0;
	while (input[*i + j + 1] && input[*i + j + 1] != c)
	{
		(*content)->str[j] = input[*i + j + 1];
		j++;
	}
	(*content)->str[j] = '\0';
	*i += 2;
}

static void	deal_with_word(char *input, int *i, t_lexem **content)
{
	int	j;

	(*content)->len = get_word_len(input, *i, ' ');
	(*content)->str = (char *)malloc(sizeof(char)
			* (get_word_len(input, *i, ' ') + 1));
	if ((*content)->str == NULL)
		exit(EXIT_FAILURE);
	j = 0;
	while (input[*i] != ' ' && input[*i] != '\n'
		&& input[*i] != '\0')
	{
		// if (input[*i] == '\"' || input[*i] == '\'')
		// 	deal_with_quotes(input, i, content);
		(*content)->str[j] = input[*i];
		j++;
		*i += 1;
	}
	(*content)->str[j] = '\0';
	(*content)->token = TOKEN_WORD;
	*i -= (*content)->len;
}

void	lexer(t_main **main, char *input)
{
	t_list	*new_lexem;
	t_lexem	*content;
	int		i;

	add_history(input);
	change_to_spaces_and_check_quotes(&input);
	(*main)->lexems = NULL;
	i = 0;
	while (input[i])
	{
		content = (t_lexem *)malloc(sizeof(t_lexem));
		if (content == NULL)
			exit(EXIT_FAILURE);
		if (input[i] == ' ' || input[i] == '|' || input[i] == '\n')
			spc_nwln_pipe(input, i, &content);
		else if (input[i] == '>' || input[i] == '<')
			deal_with_redir(input, i, &content);
		else if (input[i] == '\"' || input[i] == '\'')
			deal_with_quotes(input, &i, &content);
		else
			deal_with_word(input, &i, &content);
		new_lexem = ft_lstnew((void *)content);
		if (new_lexem == NULL)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&(*main)->lexems, new_lexem);
		i += content->len;
	}
}
