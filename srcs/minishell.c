/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:34:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/08/29 20:54:58 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	g_status = 0;

// void	skip_spaces(char **str)
// {
// 	while (**str == ' ' || **str == '\t' || **str == '\v'
// 		|| **str == '\f' || **str == '\r')
// 		*str += 1;
// }

// void	get_word(char **str)
// {
// 	int		i;
// 	char	tmp_word[20];
	
// 	i = 0;
	
// 	while (**str != ' ' && **str != '\t' && **str != '\v'
// 		&& **str != '\f' && **str != '\r' && **str)
// 	{
// 		tmp_word[i] = **str;
// 		i++;
// 		*str += 1;
// 	}
// 	tmp_word[i] = '\0';
// 	printf("%s\n", tmp_word);
// }

void	assign_token(t_list **elem)
{
	if (ft_strncmp((char *)(*elem)->content, "" )
}

t_list	*make_list(char **words)
{
	t_list	*head;
	t_list	*elem;
	int		i;

	list = ft_lstnew((void)words[0]);
	if (list == NULL)
		exit(1);
	i = 0;
	while (words[++i])
	{
		elem = ft_lstnew((void)words[i]);
		if (elem == NULL)
			exit(1);
		assign_token(&elem);
		ft_lstadd_back(&head, elem);
	}
	return (head);
}

void	change_to_spaces(char **str)
{
	int	i;
	
	while (str[0][i])
	{
		if (str[0][i] == '\t' || str[0][i] == '\v'
			|| str[0][i] == '\f' || str[0][i] == '\r')
		{
			str[0][i] = ' ';
			i++;
		}
		else
			i++;
	}
}

void	read_input(char *input)
{
	char	**words;

	add_history(input);
	// while (*input && *input != '\n')
	// {
	// 	skip_spaces(&input);
	// 	get_word(&input);
	// }
	change_to_spaces(&input);
	words = ft_split(input, ' ');
	while(*words)
	{
		printf("%s\n", *words);
		words++;
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
	while (!g_status)
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
