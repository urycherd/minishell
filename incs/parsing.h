/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 23:56:00 by qsergean          #+#    #+#             */
/*   Updated: 2022/08/21 23:46:10 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

enum e_tokens
{
	TOKEN_NEWLINE,
	TOKEN_L_BRACKET,
	TOKEN_R_BRACKET,
	TOKEN_OUT_REDIR,
	TOKEN_OUT_REDIR_AP,
	TOKEN_IN_REDIR,
	TOKEN_HEREDOC,
	TOKEN_PIPE,
	TOKEN_SEMICOLON,
	TOKEN_WORD,
	TOKEN_ENV
};

typedef struct s_nodes
{
	char			*content;
	int				index;
	e_tokens		token;
	struct s_list	*next;
	
}	t_nodes;

#endif