/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:34:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/10/03 22:17:20 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	fill_cmd_content(int size, t_command *content, t_list **iter_lexem)
{
	int	i;
	
	content->args = (char **)malloc(sizeof(char *) * (size + 1));
	if (content->args == NULL)
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < size && *iter_lexem)
	{
		while (((t_lexem *)((*iter_lexem)->content))->token == TOKEN_SEP) // это ерунда, тут нужно умнее сделать
			*iter_lexem = (*iter_lexem)->next;
		(content->args)[i] = ft_strdup(((t_lexem *)((*iter_lexem)->content))->str);
		*iter_lexem = (*iter_lexem)->next;
	}
	(content->args)[i] = NULL;
	content->redir = NULL;
}

void	join_lexems(t_main **main)
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
			((t_lexem *)(lexem->content))->len += ((t_lexem *)(next->content))->len;
			((t_lexem *)(lexem->content))->str =
				ft_strjoin_mod(((t_lexem *)(lexem->content))->str,
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

int	get_num_of_args(t_list *lexem)
{
	int	i;
	t_list	*iter;

	i = 0;
	iter = lexem;
	while (iter)
	{
		if (((t_lexem *)(iter->content))->token == TOKEN_WORD)
			i++;
		else if (((t_lexem *)(iter->content))->token == TOKEN_PIPE)
			break ;
		iter = iter->next;
	}
	return (i);
}

void	parser(t_main **main)
{
	t_list		*new_command;
	t_list		*iter_lexem;
	t_command	*content;
	int			size;

	(*main)->commands = NULL;
	iter_lexem = (*main)->lexems;
	// printf("%s\n", ((t_lexem *)(iter_lexem->content))->str);
	while (iter_lexem)
	{
		if (((t_lexem *)(iter_lexem->content))->token == TOKEN_SEP
			|| ((t_lexem *)(iter_lexem->content))->token == TOKEN_NEWLINE
			|| ((t_lexem *)(iter_lexem->content))->token == TOKEN_PIPE)
			iter_lexem = iter_lexem->next;
		else if (((t_lexem *)(iter_lexem->content))->token == TOKEN_OUT_REDIR
			|| ((t_lexem *)(iter_lexem->content))->token == TOKEN_OUT_REDIR_APPEND
			|| ((t_lexem *)(iter_lexem->content))->token == TOKEN_IN_REDIR
			|| ((t_lexem *)(iter_lexem->content))->token == TOKEN_HEREDOC)
		{
			iter_lexem = iter_lexem->next; //вот тут надо обработать бро!!!
		}
		else
		{
			content = (t_command *)malloc(sizeof(t_command));
			if (content == NULL)
				exit(EXIT_FAILURE);
			size = get_num_of_args(iter_lexem); // убрать из учета тут редиректы 
			// printf("size=%d\n", size);
			fill_cmd_content(size, content, &iter_lexem);
			new_command = ft_lstnew(content);
			ft_lstadd_back(&(*main)->commands, new_command);
			// printf("debug %s\n", ((t_lexem *)(iter_lexem->content))->str);
			// iter_lexem = iter_lexem->next;
			// printf("debug %s\n", ((t_lexem *)(iter_lexem->content))->str);
		}
	}
}

// t_list	*get_lexem_wo_sep(t_list *lexem)
// {
// 	t_list	*lexem;

// 	lexem = (*main)->lexems;
// 	while (lexem)
// 	{
// 		if (((t_lexem *)(lexem->content))->token == TOKEN_PIPE)
// 		{

// 		}
// 	}
// 	return (lexem);
// }

// int	check_lexems(t_main **main)
// {
// 	t_list	*lexem;
// 	t_list	*next;

// 	lexem = (*main)->lexems;
// 	if (lexem == NULL)
// 		return (EXIT_FAILURE);
// 	next = lexem->next;
// 	while (lexem && next)
// 	{
// 		if (((t_lexem *)(lexem->content))->token == TOKEN_PIPE
// 			&& ((t_lexem *)(next->content))->token == TOKEN_PIPE)
// 		{
// 			printf("blyaaa pipes error\n");
// 			ft_putendl_fd("parse error near |", STDERR_FILENO);
// 			return (EXIT_FAILURE);
// 		}
// 		lexem = lexem->next;
// 		next = lexem->next;
// 	}
// 	return (EXIT_SUCCESS);
// }

int	main(int argc, char **argv, char **envp)
{
	char	*input;
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
	main->exit_f = 0;
	while (main->exit_f == 0)
	{
		// rl_outstream = stderr;
		input = readline("minish-1.0$ ");
		if (input == NULL)
		{
			ft_putstr_fd("exit\n", 2);
			exit(EXIT_SUCCESS);
		}
		else if (input && *input)
		{
			if (lexer(&main, input) == EXIT_FAILURE)
			{
				free(input);
				continue ;
			}
			handle_expansions(&main);
			join_lexems(&main);
			// if (check_lexems(&main) == EXIT_FAILURE)
			// {
			// 	free(input);
			// 	continue ;
			// }
			print_lexems(&main);
			free(input);
			parser(&main);
			print_parsed(&main);
		}
		// 4.executor part
		executor(main);
		write(2, "tot\n", 4);
		// вообще надо создать нечто а-ля пайпекс с бонусами и положить в него проверку на билин или нет для случая с папами
		write(2, "okk\n", 4);
	}
	return (main->ret);
}
