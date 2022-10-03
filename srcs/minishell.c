/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:34:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/10/03 21:47:06 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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

void	ft_lstadd_after(t_list **node, t_list **new)
{
	t_list	*tmp;

	if (*node == NULL || *new == NULL)
		return ;
	tmp = (*node)->next;
	(*node)->next = *new;
	(*new)->next = tmp; 
}

t_list	*ft_lstdel_smart(t_list **list, t_list *node)
{
	t_list	*iter;
	t_list	*tmp;

	iter = (*list);
	if (iter == node)
	{
		tmp = *list;
		*list = (*list)->next;
		ft_lstdelone(tmp, free);
		return (*list);
	}
	else
	{
		while (iter)
		{
			if (iter->next == node)
				break;
			iter = iter->next;
		}
		iter->next = node->next;
		ft_lstdelone(node, free);
		return (iter);
	}
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
		while (((t_lexem *)((*iter_lexem)->content))->token == TOKEN_SEP) // это ерунда, тут нужно умнее сделать
			(*iter_lexem) = (*iter_lexem)->next;
		(content->args)[i] = ft_strdup(((t_lexem *)((*iter_lexem)->content))->str);
		*iter_lexem = (*iter_lexem)->next;
	}
	(content->args)[i] = NULL;
}

void	deal_with_word_light(char *input, int *i, t_lexem **content)
{
	int	j;

	(*content)->len = get_word_len(input, *i, ' ', 0);
	(*content)->str = (char *)malloc(sizeof(char)
			* (get_word_len(input, *i, '\0', 1) + 1));
	if ((*content)->str == NULL)
		exit(EXIT_FAILURE);
	j = 0;
	while (input[*i] != '\n' && input[*i] != '\0' 
		&& input[*i] != '$')
	{
		(*content)->str[j] = input[*i];
		j++;
		*i += 1;
	}
	(*content)->str[j] = '\0';
	(*content)->token = TOKEN_WORD;
}

void	handle_expansions(t_main **main)
{
	t_list	*lexem;
	t_list	*new_lexem;
	t_list	*save;
	t_lexem	*content;
	char	*str;
	int		i;

	lexem = (*main)->lexems;
	while (lexem)
	{
		if (((t_lexem *)(lexem->content))->token == TOKEN_DQUOTE)
		{
			save = lexem;
			str = *(&((t_lexem *)(lexem->content))->str);
			i = 0;
			while (str && str[i])
			{
				content = (t_lexem *)malloc(sizeof(t_lexem));
				if (content == NULL)
					exit(EXIT_FAILURE);
				if (str[i] == '$')
					deal_with_dollar(str, &i, &content);
				else if (str && str[i])
					deal_with_word_light(str, &i, &content);
				new_lexem = ft_lstnew(content);
				if (new_lexem == NULL)
					exit(EXIT_FAILURE);
				ft_lstadd_after(&save, &new_lexem);
				save = save->next;
			}
			ft_lstdel_smart(&(*main)->lexems, lexem);
			lexem = save;
		}
		lexem = lexem->next;
	}
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
			if (lexer(&main, input) == EXIT_FAILURE)
			{
				free(input);
				continue ;
			} 
			handle_expansions(&main);
			join_lexems(&main);
			print_lexems(&main);
			free(input);
			parser(&main);
			print_parsed(&main);
		}
		// 4.executor part
		executor(main);
		// вообще надо создать нечто а-ля пайпекс с бонусами и положить в него проверку на билин или нет для случая с папами
	}
	return (main->ret);
}
