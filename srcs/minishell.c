/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:34:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/09/13 23:52:09 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	g_status = OK;

// void	skip_spaces(char **str)
// {
// 	while (**str == ' ' || **str == '\t' || **str == '\v'
// 		|| **str == '\f' || **str == '\r')
// 		*str += 1;
// }

// void	get_word(char **str)
// {
// 	int		i;
// 	char	tmp_word[20];
	
// 	i = 0;
	
// 	while (**str != ' ' && **str != '\t' && **str != '\v'
// 		&& **str != '\f' && **str != '\r' && **str)
// 	{
// 		tmp_word[i] = **str;
// 		i++;
// 		*str += 1;
// 	}
// 	tmp_word[i] = '\0';
// 	printf("%s\n", tmp_word);
// }

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

void	change_to_spaces(char **str)
{
	int	i;
	
	i = 0;
	while (str[0][i])
	{
		if (str[0][i] == '\t' || str[0][i] == '\v'
			|| str[0][i] == '\f' || str[0][i] == '\r')
		{
			str[0][i] = ' ';
			i++;
		}
		else
			i++;
	}
}

void	old_lexer(t_main **main, char *input)
{
	char	**words;

	add_history(input);
	// while (*input && *input != '\n')
	// {
	// 	skip_spaces(&input);
	// 	get_word(&input);
	// }
	change_to_spaces(&input);
	words = ft_split(input, ' ');
	while(*words)
	{
		printf("%s\n", *words);
		words++;
	}
}

void	lexer(t_main **main, char *input)
{
	int		i;
	int		word_len;
	char	*word;
	t_list	*new_lexem;

	change_to_spaces(&input);
	i = -1;	
	while (input[++i])
	{
		if (input[i] == ' ')
		{
			new_lexem = ft_lstnew(" ");
			new_lexem->token = TOKEN_SEP;
			new_lexem->len = 1;
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				new_lexem = ft_lstnew(">>");
				new_lexem->token = TOKEN_OUT_REDIR_APPEND;
				new_lexem->len = 2;
				i++;
			}
			else
			{
				new_lexem = ft_lstnew(">");
				new_lexem->token = TOKEN_OUT_REDIR;
				new_lexem->len = 1;
			}
		}
		else if (input[i] == '<')
		{
			if (input[i + 1] == '<')
			{
				new_lexem = ft_lstnew("<<");
				new_lexem->token = TOKEN_HEREDOC;
				new_lexem->len = 2;
				i++;
			}
			else
			{
				new_lexem = ft_lstnew("<");
				new_lexem->token = TOKEN_IN_REDIR;
				new_lexem->len = 1;
			}
		}
		else if (input[i] == '|')
		{
			new_lexem = ft_lstnew("|");
			new_lexem->token = TOKEN_PIPE;
			new_lexem->len = 1;
		}
		else
		{
			word_len = 0;
			while (input[i] != ' ' && input[i] != '\n'
				&& input[i] != '\0')
			{
				word[word_len] = input[i];
				word_len++;
				i++;
			}
			new_lexem = ft_lstnew(word);
			new_lexem->token = TOKEN_WORD;
			new_lexem->len = word_len;
			i--;
		}
		ft_lstadd_back(&(*main)->lexems, new_lexem);
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
			exit(0);
		}
		// 2.lexer part
		else if (input && *input)
			lexer(&main, input);
		// 3.parser part
	}

	// 4.executor part
	
}
