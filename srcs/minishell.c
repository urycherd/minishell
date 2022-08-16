/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:34:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/08/16 23:40:58 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGQUIT || sig == SIGINT) // ctrl backslash
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	deal_with_signals(void)
{
	struct sigaction	act;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = signal_handler;
	sigaction(SIGINT, &act, 0);
	sigaction(SIGQUIT, &act, 0);
}

int	main(int argc, char **argv, char **envp)
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
	deal_with_signals();
	ft_putstr_fd("minish-1.0$ ", 1);
	read = NULL;
	while (1)
	{
		input = readline(read);
		if (input == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		// read_input(read);
		ft_putstr_fd("minish-1.0$ ", 1);
	}
	printf("%s\n", readline(read));
}
