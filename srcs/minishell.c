/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:34:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/08/16 00:28:08 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*read;
	char	*input;

	(void)argv;
	(void)envp;
	if (argc != 1)
	{
		ft_putstr_fd("Input error! No arguments are allowed.\n", 1);
		return (-1);
	}
	ft_putstr_fd("minish-1.0$ ", 1);
	read = NULL;
	while (1)
	{
		input = readline(read);
		ft_putstr_fd("minish-1.0$ ", 1);
	}
	printf( "%s\n", readline(read) );
	// printf("$s\n", read);
}