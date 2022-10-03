/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:42:06 by qsergean          #+#    #+#             */
/*   Updated: 2022/10/02 16:53:40 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	deal_with_dollar(char *input, int *i, t_lexem **content)
{
	char	*after_dollar;
	int		len;
	int		j;
	char	*res;

	*i += 1;
	len = get_word_len(input, *i, ' ', 0);
	after_dollar = (char *)malloc(sizeof(char) * (len + 2));
	if (after_dollar == NULL)
		exit(EXIT_FAILURE);
	after_dollar[0] = '$';
	j = 1;
	while (input[*i] && input[*i] != ' '
		&& input[*i] != '\n' && input[*i] != '$'
		&& input[*i] != '\"' && input[*i] != '\'')
	{
		after_dollar[j] = input[*i];
		j++;
		*i += 1;
	}
	after_dollar[j] = '\0';
	res = getenv(&after_dollar[1]);
	(*content)->token = TOKEN_WORD;
	if (res == NULL)
	{
		(*content)->len = 0;
		(*content)->str = ft_strdup("");
	}
	else
	{
		(*content)->len = ft_strlen(res);
		(*content)->str = ft_strdup(res);
	}
	free(after_dollar);
}

static void	deal_with_redir(char *input, int *i, t_lexem **content)
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
	else if (input[*i] == '<')
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

static void	spc_nwln_pipe(char *input, int *i, t_lexem **content)
{
	if (input[*i] == ' ')
	{
		(*content)->str = " ";
		(*content)->token = TOKEN_SEP;
		(*content)->len = 1;
	}
	else if (input[*i] == '|')
	{
		(*content)->str = "|";
		(*content)->token = TOKEN_PIPE;
		(*content)->len = 1;
	}
	else if (input[*i] == '\n')
	{
		(*content)->str = " ";
		(*content)->token = TOKEN_NEWLINE;
		(*content)->len = 1;
	}
	*i += 1;
}

static void	deal_with_quotes(char *input, int *i, t_lexem **content)
{
	int		j;
	char	c;

	if ((*content)->len == 0)
	{
		free(*content);
		*i += 2;
		return ;
	}
	c = input[*i];
	(*content)->len = get_word_len(input, *i + 1, c, 0);
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
	*i += (*content)->len + 2;
}

static void	deal_with_word(char *input, int *i, t_lexem **content)
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
		&& input[*i] != '\'' && input[*i] != '\'' // почему тут два раза??
		&& input[*i] != '|')
	{
		// if (input[*i] == '\"' || input[*i] == '\'')
		// 	deal_with_quotes(input, i, content);
		(*content)->str[j] = input[*i];
		j++;
		*i += 1;
	}
	(*content)->str[j] = '\0';
	(*content)->token = TOKEN_WORD;
}

int	lexer(t_main **main, char *input)
{
	t_list	*new_lexem;
	t_lexem	*content;
	int		i;

	add_history(input);
	if (change_to_spaces_and_check_quotes(&input) < 0)
	{
		return (EXIT_FAILURE);
	}
	(*main)->lexems = NULL;
	i = 0;
	while (input[i])
	{
		content = (t_lexem *)malloc(sizeof(t_lexem));
		if (content == NULL)
			exit(EXIT_FAILURE);
		if (input[i] == ' ' || input[i] == '|' || input[i] == '\n')
			spc_nwln_pipe(input, &i, &content);
		else if (input[i] == '>' || input[i] == '<')
			deal_with_redir(input, &i, &content);
		else if (input[i] == '\"' || input[i] == '\'')
			deal_with_quotes(input, &i, &content);
		else if (input[i] == '$')
			deal_with_dollar(input, &i, &content);
		else
			deal_with_word(input, &i, &content);
		new_lexem = ft_lstnew((void *)content);
		if (new_lexem == NULL)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&(*main)->lexems, new_lexem);
		// i += content->len;
		// printf("%s, %d\n", content->str, i);
	}
	return (EXIT_SUCCESS);
}
