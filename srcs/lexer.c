/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:42:06 by qsergean          #+#    #+#             */
/*   Updated: 2022/10/13 20:03:16 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// void	dollar_helper()
// {

// }

void	deal_with_dollar(t_main *main, char *input, int *i, t_lexem **content)
{
	char	*after_dollar;
	int		j;
	char	*res;

	*i += 1;
	if (input[*i] == '\0' || input[*i] == '$' || input[*i] == '?')
	{
		if (input[*i] == '$')
		{
			res = ft_itoa(getpid());
			*i += 1;
		}
		else if (input[*i] == '?')
		{
			res = ft_itoa(main->exit_f);
			*i += 1;
		}
		else
			res = "$";
	}
	else
	{
		after_dollar = (char *)malloc(sizeof(char)
				* (get_word_len(input, *i, ' ', 0) + 2));
		if (after_dollar == NULL)
			exit(EXIT_FAILURE);
		after_dollar[0] = '$';
		j = 1;
		while (input[*i] && input[*i] != ' ' && input[*i] != '\n'
			&& input[*i] != '$' && input[*i] != '\"' && input[*i] != '\'')
			after_dollar[j++] = input[(*i)++];
		after_dollar[j] = '\0';
		res = ft_getenv(main->env, &after_dollar[1]);
		free(after_dollar);
	}
	(*content)->token = TOKEN_WORD;
	if (res == NULL)
		(*content)->str = ft_strdup("");
	else
		(*content)->str = ft_strdup(res);
	(*content)->len = ft_strlen((*content)->str);
}

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

static void	deal_with_redir(char *input, int *i, t_lexem **content)
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

static void	spc_nwln_pipe(char *input, int *i, t_lexem **content)
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

static void	deal_with_quotes(char *input, int *i, t_lexem **content)
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

void	lexer_body(t_main *main, char *input, t_lexem **content, int *i)
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
