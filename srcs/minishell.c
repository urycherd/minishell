/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:34:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/08/14 23:52:08 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int main(int argc, char **argv, char **envp)
{
	int i;
	char *read;

	(void)argv;
	(void)argc;
	read = NULL;
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	printf( "%s\n", readline(read) );
	// printf("$s\n", read);
}