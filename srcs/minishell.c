/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:34:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/08/25 00:00:14 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
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

void	skip_spaces(char **str)
{
	while (**str == ' ' || **str == '\t' || **str == '\v'
		|| **str == '\f' || **str == '\r')
		*str += 1;
}

void	get_word(char **str)
{
	int		i;
	char	*tmp_word;
	
	i = 0;
	tmp_word = "";
	
	while (**str != ' ' && **str != '\t' && **str != '\v'
		&& **str != '\f' && **str != '\r')
	{
		tmp_word[i] = **str;
		i++;
		*str += 1;
	}
	tmp_word[i] = '\0';
	printf("%s\n", tmp_word);
}

void	read_input(char *input)
{
	add_history(input);
	while (*input && *input != '\n')
	{
		skip_spaces(&input);
		get_word(&input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argv;
	(void)envp;
	if (argc != 1)
	{
		ft_putstr_fd("Input error! No arguments are allowed.\n", 1);
		return (-1);
	}
	deal_with_signals();
	// while (*envp)
	// {
	// 	printf("%s\n", *envp);
	// 	envp++;
	// }
	printf("\v");
	while (1)
	{
		// rl_outstream = stderr;
		input = readline("minish-1.0$ ");
		if (input == NULL)
		{
			ft_putstr_fd("exit\n", 2);
			exit(0);
		}
		else if (input && *input)
			read_input(input);
	}
}
