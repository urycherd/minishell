/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:34:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/09/18 00:23:50 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	g_status = OK;

// void	assign_token(t_list **elem)
// {
// 	if (ft_strncmp((char *)(*elem)->content, "" )
// }

t_list	*make_list(char **words)
{
	t_list	*head;
	t_list	*elem;
	int		i;

	head = ft_lstnew((void *)words[0]);
	if (head == NULL)
		exit(1);
	i = 0;
	while (words[++i])
	{
		elem = ft_lstnew((void *)words[i]);
		if (elem == NULL)
			exit(1);
		// assign_token(&elem);
		ft_lstadd_back(&head, elem);
	}
	return (head);
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
		exit(EXIT_FAILURE);
	}
	return (i);
}

int	get_word_len(char *str, int i, char c)
{
	int	res;

	res = 0;
	while (str[i + res] && str[i + res] != c
		&& str[i] != '\n')
		res++;
	return (res);
}

// void	deal_with_quotes(t_list **new_lexem, char *input, int *i, char quote)
// {
// 	int		len;
// 	int		j;

// 	*i += 1;
// 	len = get_word_len(input, *i, quote);
// 	word = (char *)malloc(sizeof(char) * len);
// 	if (word == NULL)
// 		exit(EXIT_FAILURE);
// 	j = 0;
// 	while (input[*i] != quote)
// 	{
// 		word[j] = input[*i];
// 		j++;
// 		*i += 1;
// 	}
// 	word[j] = '\0';
// 	*new_lexem = ft_lstnew(word);
// 	(*new_lexem)->len = len;
// 	(*new_lexem)->token = TOKEN_WORD;
// 	if ((*new_lexem)->content == NULL)
// 		exit(EXIT_FAILURE);
// }

char	*deal_with_dollar(char *input, int *i)
{
	char	*after_dollar;
	int		len;
	int		j;

	len = get_word_len(input, *i, ' ') + 1;
	after_dollar = (char *)malloc(sizeof(char) * len);
	if (after_dollar == NULL)
		exit(EXIT_FAILURE);
	*i += 1;
	j = 0;
	while (input[*i] && input[*i] != ' '
		&& input[*i] != '\n' && input[*i] != '$')
	{
		after_dollar[j] = input[*i];
		j++;
		*i += 1;
	}
	after_dollar[j] = '\0';
	return (ft_strdup(getenv(after_dollar))); 
}

void	lexer(t_main **main, char *input)
{
	t_list	*new_lexem;
	t_lexem	*content;
	int		input_len;
	int		i;
	int		j;

	add_history(input);
	input_len = change_to_spaces_and_check_quotes(&input);
	(*main)->lexems = NULL;
	i = 0;
	while (input[i])
	{
		content = (t_lexem *)malloc(sizeof(t_lexem));
		if (content == NULL)
			exit(EXIT_FAILURE);
		if (input[i] == ' ')
		{
			content->str = " ";
			content->token = TOKEN_SEP;
			content->len = 1;
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				content->str = ">>";
				content->token = TOKEN_OUT_REDIR_APPEND;
				content->len = 2;
			}
			else
			{
				content->str = ">";
				content->token = TOKEN_OUT_REDIR;
				content->len = 1;
			}
		}
		else if (input[i] == '<')
		{
			if (input[i + 1] == '<')
			{
				content->str = "<<";
				content->token = TOKEN_HEREDOC;
				content->len = 2;
			}
			else
			{
				content->str = "<";
				content->token = TOKEN_IN_REDIR;
				content->len = 1;
			}
		}
		else if (input[i] == '|')
		{
			content->str = "|";
			content->token = TOKEN_PIPE;
			content->len = 1;
		}
		else if (input[i] == '\n')
		{
			content->str = " ";
			content->token = TOKEN_NEWLINE;
			content->len = 1;
		}
		else if (input[i] == '\"')
		{
			content->len = get_word_len(input, i + 1, '\"') + 2;
			if (content->len == 2)
			{
				free(content);
				i += 2;
				continue ;
			}
			content->token = TOKEN_WORD;
			content->str = (char *)malloc(sizeof(char) * (content->len + 1));
			if (content->str == NULL)
				exit(EXIT_FAILURE);
			content->str[0] = '\"';
			j = 1;
			while (input[i + 1] != '\"')
			{
				if (input[i + 1] == '$')
					content->str = deal_with_dollar(input, &i);
				content->str[j] = input[i + 1];
				j++;
				i++;
			}
			content->str[j] = '\"';
			content->str[j + 1] = '\0';
			i -= content->len - 2;
		}
		else
		{
			content->len = get_word_len(input, i, ' ');
			content->str = (char *)malloc(sizeof(char) * (get_word_len(input, i, ' ') + 1));
			if (content->str == NULL)
				exit(EXIT_FAILURE);
			j = 0;
			while (input[i] != ' ' && input[i] != '\n'
				&& input[i] != '\0')
			{
				content->str[j] = input[i];
				j++;
				i++;
			}
			content->str[j] = '\0';
			content->token = TOKEN_WORD;
			i -= content->len;
		}
		new_lexem = ft_lstnew((void *)content);
		if (new_lexem == NULL)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&(*main)->lexems, new_lexem);
		i += content->len;
	}
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

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_info	info; //  Саш, это нужно?
	t_main	*main;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Input error! No arguments are allowed.\n", 1);
		return (EXIT_FAILURE);
	}
	deal_with_signals();
	main = (t_main *)malloc(sizeof(t_main));
	if (main == NULL)
		return (EXIT_FAILURE);
	make_env_list(&main, envp);
	// нужно проиницилизировать частично исходную структуру тут
	info.exit_f = 0; //  Саш, это нужно?
	while (g_status == OK)
	{
		// rl_outstream = stderr;
		// 1.readline part
		input = readline("minish-1.0$ ");
		if (input == NULL)
		{
			ft_putstr_fd("exit\n", 2);
			exit(EXIT_SUCCESS);
		}
		// 2.lexer part
		else if (input && *input)
		{
			lexer(&main, input);
			print_lexems(&main);
		}
		// 3.parser part
		free(input);
	}

	// 4.executor part
	
}
