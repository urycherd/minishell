/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:34:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/09/30 13:03:30 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// char	*ft_realloc(ptr, newSize)
//     // char 	 *ptr;		
// 				/* Ptr to currently allocated block.  If
// 				 * it's 0, then this procedure behaves
// 				 * identically to malloc. */
//     // unsigned int newSize;	/* Size of block after it is extended */
// {
//     unsigned int curSize;
//     char *newPtr;
//     if (ptr == 0)
// 	{
// 		return (malloc(newSize));
//     }
//     curSize = Mem_Size(ptr);
//     if (newSize <= curSize)
// 	{
// 		return (ptr);
//     }
//     newPtr = malloc(newSize);
//     ft_memcpy(ptr, newPtr, (size_t)curSize);
//     free(ptr);
//     return (newPtr);
// }

// char	*deal_with_dollar(char *input, int *i)
// {
// 	char	*after_dollar;
// 	int		len;
// 	int		j;
// 	len = get_word_len(input, *i, ' ') + 1;
// 	after_dollar = (char *)malloc(sizeof(char) * len);
// 	if (after_dollar == NULL)
// 		exit(EXIT_FAILURE);
// 	*i += 1;
// 	j = 0;
// 	while (input[*i] && input[*i] != ' '
// 		&& input[*i] != '\n' && input[*i] != '$'
// 		&& input[*i] != '\"' && input[*i] != '\'')
// 	{
// 		after_dollar[j] = input[*i];
// 		j++;
// 		*i += 1;
// 	}
// 	after_dollar[j] = '\0';
// 	return (ft_strdup(getenv(after_dollar))); 
// }

// void	parse_dollars(t_main **main)
// {
// 	t_list	*iter_lexem;
	
// 	iter_lexem = (*main)->lexems;
// 	while (iter_lexem)
// 	{
		
// 	}
// }

int	get_num_of_args(t_list *lexem)
{
	int	i;
	t_list	*iter;

	i = 0;
	iter = lexem;
	while (iter)
	{
		if ((((t_lexem *)(iter)->content))->token == TOKEN_DQUOTE
			|| ((t_lexem *)(iter->content))->token == TOKEN_WORD)
			i++;
		else if (((t_lexem *)(iter->content))->token == TOKEN_PIPE)
			break ;
		iter = iter->next;
	}
	return (i);
}

void	fill_cmd_content(int size, t_command *content, t_list **iter_lexem)
{
	int	i;
	
	content->args = (char **)malloc(sizeof(char *) * (size + 1));
	if (content->args == NULL)
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < size && *iter_lexem)
	{
		// // printf("%p\n", ((t_lexem *)((*iter_lexem)->content))->str);
		// if (((t_lexem *)((*iter_lexem)->content))->token == TOKEN_PIPE)
		// 	break ;
		// printf("biba\n");
		while (((t_lexem *)((*iter_lexem)->content))->token == TOKEN_SEP) // это ерунда, тут нужно умнее сделать
		{
			// printf("%d\n", i);
			(*iter_lexem) = (*iter_lexem)->next;
		}
		(content->args)[i] = ft_strdup(((t_lexem *)((*iter_lexem)->content))->str);
		*iter_lexem = (*iter_lexem)->next;
	}
	(content->args)[i] = NULL;
	// printf("Exit\n");
}

// void	handle_expansions(t_main **main)
// {
// 	t_list	*lexem;
// 	t_lexem	*content;
// 	t_list	*new_lexem;
// 	// int		flag_quotes;
// 	char	**str;
// 	int		i;

// 	lexem = (*main)->lexems;
// 	while (lexem)
// 	{
// 		if (((t_lexem *)(lexem->content))->token == TOKEN_DQUOTE)
// 		{
// 			// flag_quotes = 1;
// 			content = (t_lexem *)malloc(sizeof(t_lexem));
// 			if (content == NULL)
// 				exit(EXIT_FAILURE);
// 			str = &((t_lexem *)(lexem->content))->str;
// 			i = -1;
// 			while (str[0] && str[0][++i])
// 			{
// 				// if (str[0][i] == '\'')
// 				// 	flag_quotes *= -1;
// 				if (str[0][i] == '$') //&& flag_quotes > 0)
// 				{
// 					deal_with_dollar(str[0], &i, &content);
// 					new_lexem = ft_lstnew(content);
// 					if (new_lexem == NULL)
// 						exit(EXIT_FAILURE);
// 					ft_lstadd_after
// 				}
// 			}
// 			lexem
// 			ft_lstdelone(lexem);
// 		}
// 		lexem = lexem->next;
// 	}
// }

void	join_lexems(t_main **main)
{
	t_list	*lexem;
	t_list	*next;

	lexem = (*main)->lexems;
	next = lexem->next;
	while (lexem && next)
	{
		if ((((t_lexem *)(lexem->content))->token == TOKEN_WORD
			|| ((t_lexem *)(lexem->content))->token == TOKEN_DQUOTE)
			&& (((t_lexem *)(next->content))->token == TOKEN_WORD
			|| ((t_lexem *)(next->content))->token == TOKEN_DQUOTE))
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

void	parser(t_main **main)
{
	t_list		*new_command;
	t_list		*iter_lexem;
	t_command	*content;
	int			size;

	// parse_dollars(main);
	// handle_expansions(main);
	(*main)->commands = NULL;
	iter_lexem = (*main)->lexems;
	
	// printf("%s\n", ((t_lexem *)(iter_lexem->content))->str);
	while (iter_lexem)
	{
		if (((t_lexem *)(iter_lexem->content))->token == TOKEN_SEP
			|| ((t_lexem *)(iter_lexem->content))->token == TOKEN_NEWLINE
			|| ((t_lexem *)(iter_lexem->content))->token == TOKEN_PIPE)
			iter_lexem = iter_lexem->next;
		// else if (((t_lexem *)(iter_lexem->content))->token == TOKEN_WORD
		// 	|| ((t_lexem *)(iter_lexem->content))->token == TOKEN_DQUOTE)

		else
		{
			content = (t_command *)malloc(sizeof(t_command));
			if (content == NULL)
				exit(EXIT_FAILURE);
			size = get_num_of_args(iter_lexem);
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

void	print_parsed(t_main **main)
{
	t_list		*iter;
	t_command	*cmd;
	int			i;
	int			j;

	printf("\n**************\n");
	iter = (*main)->commands;
	j = 1;
	while (iter)
	{
		printf("Group number %d:\n", j);
		cmd = iter->content;
		i = 0;
		while (cmd->args[i])
		{
			printf("%s ", (cmd->args)[i]);
			i++;
		}
		iter = iter->next;
		j++;
		printf("\n");
	}
	printf("**************\n\n");
}

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
			join_lexems(&main);
			print_lexems(&main);
		}
		// 3.parser part
		free(input);
		parser(&main);
		print_parsed(&main);
		if (!ft_strcmp(((t_command *)(main->commands->content))->args[0], "cd"))
			ft_cd(main, ((t_command *)(main->commands->content))->args);
		else if (!ft_strcmp(((t_command *)(main->commands->content))->args[0], "echo"))
			ft_echo(((t_command *)(main->commands->content))->args);
		else if (!ft_strcmp(((t_command *)(main->commands->content))->args[0], "env"))
		{
			if (((t_command *)(main->commands->content))->args[1])
				return (1); //error too many args
			ft_env(main->env);
		}
		else if (!ft_strcmp(((t_command *)(main->commands->content))->args[0], "exit"))
			ft_exit(main, ((t_command *)(main->commands->content))->args);
		else if (!ft_strcmp(((t_command *)(main->commands->content))->args[0], "export"))
			ft_export(&main, ((t_command *)(main->commands->content))->args);
		else if (!ft_strcmp(((t_command *)(main->commands->content))->args[0], "pwd"))
			ft_pwd();
		else if (!ft_strcmp(((t_command *)(main->commands->content))->args[0], "unset"))
			ft_unset(&main, ((t_command *)(main->commands->content))->args);
		// 4.executor part
		// if no pipes
		// 	if builtin
		// 		call builtin
		// 	else
		//		fork
		// else
		//	if builtin {
		//		call builtin
		//		save result to tmp file
		//	}
		//	else
		//		common pipex
		// вообще надо создать нечто а-ля пайпекс с бонусами и положить в него проверку на билин или нет для случая с папами
	}
	return (main->ret);
}
