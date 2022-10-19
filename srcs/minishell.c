/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:34:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/10/14 20:43:03 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	free_all(t_main **main, char **input)
{
	t_command	*cmds;

	free(*input);
	if ((*main)->lexems)
		ft_lstclear(&(*main)->lexems, free);
	if ((*main)->commands)
	{
		cmds = (*main)->commands->content;
		ft_lstclear(&cmds->redir, free);
		ft_lstclear(&(*main)->commands, free);
	}
}

static t_list	*get_shlvl(t_list *env)
{
	while (env)
	{
		if (ft_strncmp("SHLVL", env->content, 5) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static void	shlvl_init(t_main **main)
{
	t_list	*shlvl;
	int		level;

	shlvl = get_shlvl((*main)->env);
	level = ft_atoi(shlvl->content + 6);
	shlvl->content = ft_strjoin("SHLVL=", ft_itoa(level + 1));
}

static void	preparation(int argc, char **argv, t_main *main, char **envp)
{
	(void)argv;
	(void)argc;
	make_env_list(&main, envp);
	shlvl_init(&main);
	deal_with_signals(&main);
	main->exit_f = 0;
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_main	*main;

	main = (t_main *)malloc(sizeof(t_main));
	if (main == NULL)
		return (EXIT_FAILURE);
	preparation(argc, argv, main, envp);
	while (main->exit_f == 0)
	{
		input = readline("minish-1.0$ ");
		if (input == NULL)
		{
			ft_putstr_fd("exit\n", 2);
			return (main->ret);
		}
		else if (input && *input)
		{
			if (preparsing(&main, input) == EXIT_FAILURE)
				continue ;
			parser(&main);
			executor(main);
			free_all(&main, &input);
		}
	}
	return (main->ret);
}
