/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:23:47 by qsergean          #+#    #+#             */
/*   Updated: 2022/10/14 00:27:14 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	fill_cmd_content_2(t_command *content, t_list **iter_lexem,
	int n_filenames, t_redir *redir)
{
	int	i;

	if (redir->filename == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < n_filenames)
	{
		redir->filename[i]
			= ft_strdup(((t_lexem *)((*iter_lexem)->content))->str);
		i++;
		*iter_lexem = get_lexem_wo_sep((*iter_lexem)->next);
		if (content->args == NULL)
			break ;
	}
	redir->filename[i] = NULL;
}

static void	fill_cmd_content_1(t_command *content, t_list **iter_lexem)
{
	int		n_filenames;
	t_redir	*redir;
	t_list	*new_redir;	

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
		fill_cmd_content_2(content, iter_lexem, n_filenames, redir);
		new_redir = ft_lstnew(redir);
		if (new_redir == NULL)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&(content->redir), new_redir);
		if (content->args == NULL)
			return ;
	}
	else
		*iter_lexem = (*iter_lexem)->next;
}

static void	fill_cmd_content_0(t_command *content, t_list **iter_lexem,
	int n_args)
{
	int	i;

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

static void	fill_cmd_content(t_command *content, t_list **iter_lexem)
{
	int		n_args;
	int		n_redirs;

	n_args = get_num_of_args(*iter_lexem);
	if (n_args > 0)
		fill_cmd_content_0(content, iter_lexem, n_args);
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
			fill_cmd_content_1(content, iter_lexem);
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
