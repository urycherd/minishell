/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:34:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/10/11 22:49:53 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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
			((t_lexem *)(lexem->content))->len
				+= ((t_lexem *)(next->content))->len;
			((t_lexem *)(lexem->content))->str
				= ft_strjoin_mod(((t_lexem *)(lexem->content))->str,
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

int	is_redir(t_list *lexem)
{
	if (((t_lexem *)(lexem->content))->token == TOKEN_OUT_REDIR
		|| ((t_lexem *)(lexem->content))->token == TOKEN_OUT_REDIR_APPEND
		|| ((t_lexem *)(lexem->content))->token == TOKEN_IN_REDIR
		|| ((t_lexem *)(lexem->content))->token == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	get_num_of_args(t_list *lexem)
{
	int		i;
	t_list	*iter;

	i = 0;
	iter = lexem;
	while (iter)
	{
		if (((t_lexem *)(iter->content))->token == TOKEN_WORD)
			i++;
		else if (((t_lexem *)(iter->content))->token == TOKEN_PIPE
			|| is_redir(iter))
			break ;
		iter = iter->next;
	}
	return (i);
}

int	get_num_of_redirs(t_list *lexem)
{
	int		i;
	t_list	*iter;

	i = 0;
	iter = lexem;
	while (iter)
	{
		if (is_redir(iter))
			i++;
		else if (((t_lexem *)(iter->content))->token == TOKEN_PIPE)
			break ;
		iter = iter->next;
	}
	return (i);
}

t_list	*get_lexem_wo_sep(t_list *lexem)
{
	while (lexem)
	{
		if (((t_lexem *)(lexem->content))->token == TOKEN_SEP)
			lexem = lexem->next;
		else
			return (lexem);
	}
	return (lexem);
}

void	fill_cmd_content(t_command *content, t_list **iter_lexem)
{
	int		i;
	int		n_args;
	int		n_redirs;
	int		n_filenames;
	t_redir	*redir;
	t_list	*new_redir;	

	n_args = get_num_of_args(*iter_lexem);
	if (n_args > 0)
	{
		content->args = (char **)malloc(sizeof(char *) * (n_args + 1));
		if (content->args == NULL)
			exit(EXIT_FAILURE);
		i = 0;
		while (*iter_lexem)
		{
			if ((((t_lexem *)((*iter_lexem)->content))->token == TOKEN_PIPE
				|| is_redir(*iter_lexem)))
				break ;
			else if (((t_lexem *)((*iter_lexem)->content))->token == TOKEN_WORD)
			{
				(content->args)[i]
					= ft_strdup(((t_lexem *)((*iter_lexem)->content))->str);
				i++;
			}
			*iter_lexem = (*iter_lexem)->next;
		}
		(content->args)[i] = NULL;
	}
	else
		content->args = NULL;
	n_redirs = get_num_of_redirs(*iter_lexem);
	content->redir = NULL;
	if (n_redirs == 0)
		content->redir = NULL;
	else
	{
		while (*iter_lexem
			&& ((t_lexem *)((*iter_lexem)->content))->token != TOKEN_PIPE)
		{
			if (is_redir(*iter_lexem))
			{
				redir = (t_redir *)malloc(sizeof(t_redir));
				if (redir == NULL)
					exit(EXIT_FAILURE);
				redir->token = ((t_lexem *)((*iter_lexem)->content))->token;
				*iter_lexem = get_lexem_wo_sep((*iter_lexem)->next);
				n_filenames = get_num_of_args(*iter_lexem);
				redir->filename
					= (char **)malloc(sizeof(char *) * (n_filenames + 1));
				if (redir->filename == NULL)
					exit(EXIT_FAILURE);
				i = 0;
				while (i < n_filenames)
				{
					redir->filename[i]
						= ft_strdup(((t_lexem *)((*iter_lexem)->content))->str);
					i++;
					*iter_lexem = get_lexem_wo_sep((*iter_lexem)->next);
				}
				redir->filename[i] = NULL;
				new_redir = ft_lstnew(redir);
				if (new_redir == NULL)
					exit(EXIT_FAILURE);
				ft_lstadd_back(&(content->redir), new_redir);
			}
			else
			{
				*iter_lexem = (*iter_lexem)->next;
			}
		}
	}
}

void	parser(t_main **main)
{
	t_list		*new_command;
	t_list		*iter_lexem;
	t_command	*content;

	(*main)->commands = NULL;
	iter_lexem = (*main)->lexems;
	while (iter_lexem)
	{
		if (((t_lexem *)(iter_lexem->content))->token == TOKEN_WORD
			|| is_redir(iter_lexem))
		{
			content = (t_command *)malloc(sizeof(t_command));
			if (content == NULL)
				exit(EXIT_FAILURE);
			fill_cmd_content(content, &iter_lexem);
			new_command = ft_lstnew(content);
			ft_lstadd_back(&(*main)->commands, new_command);
		}
		else
			iter_lexem = iter_lexem->next;
	}
}

int	check_lexems_body(t_list **lexem, t_list **next)
{
	while (*lexem && *next)
	{
		if (((((t_lexem *)((*lexem)->content))->token == TOKEN_PIPE
				|| is_redir(*lexem))
			&& (((t_lexem *)((*next)->content))->token == TOKEN_PIPE
			|| is_redir(*next)))
			|| (is_redir(*lexem) && (((t_lexem *)((*next)->content))->token
			!= TOKEN_WORD)))
		{
			ft_putendl_fd("minish: parse error", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		*lexem = (*lexem)->next;
		*next = get_lexem_wo_sep((*lexem)->next);
	}
	return (EXIT_SUCCESS);
}

int	check_lexems(t_main **main)
{
	t_list	*lexem;
	t_list	*next;

	lexem = (*main)->lexems;
	if (lexem == NULL)
		return (EXIT_FAILURE);
	next = get_lexem_wo_sep(lexem->next);
	if (check_lexems_body(&lexem, &next) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if ((((t_lexem *)(lexem->content))->token == TOKEN_PIPE
		|| is_redir(lexem)) && next == NULL)
	{
		ft_putendl_fd("minish: parse error", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_main	*main;

	(void)argv;
	if (argc != 1)
	{
		ft_putendl_fd("Input error! No arguments are allowed.", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	rl_outstream = stderr;
	deal_with_signals();
	main = (t_main *)malloc(sizeof(t_main));
	if (main == NULL)
		return (EXIT_FAILURE);
	make_env_list(&main, envp);
	main->exit_f = 0;
	while (main->exit_f == 0)
	{
		input = readline("minish-1.0$ ");
		if (input == NULL)
		{
			ft_putstr_fd("exit\n", 2);
			return (main->ret);
			// exit(EXIT_SUCCESS);
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
			if (check_lexems(&main) == EXIT_FAILURE)
			{
				free(input);
				continue ;
			}
			// print_lexems(&main);
			free(input);
			parser(&main);
			// print_parsed(&main);
			executor(main);
		}
	}
	return (main->ret);
}
