/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urycherd <urycherd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:34:57 by qsergean          #+#    #+#             */
/*   Updated: 2022/09/23 20:06:13 by urycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// char	*ft_realloc(ptr, newSize)
//     // char 	 *ptr;		
// 				/* Ptr to currently allocated block.  If
// 				 * it's 0, then this procedure behaves
// 				 * identically to malloc. */
//     // unsigned int newSize;	/* Size of block after it is extended */
// {
//     unsigned int curSize;
//     char *newPtr;
//     if (ptr == 0)
// 	{
// 		return (malloc(newSize));
//     }
//     curSize = Mem_Size(ptr);
//     if (newSize <= curSize)
// 	{
// 		return (ptr);
//     }
//     newPtr = malloc(newSize);
//     ft_memcpy(ptr, newPtr, (size_t)curSize);
//     free(ptr);
//     return (newPtr);
// }

// char	*deal_with_dollar(char *input, int *i)
// {
// 	char	*after_dollar;
// 	int		len;
// 	int		j;
// 	len = get_word_len(input, *i, ' ') + 1;
// 	after_dollar = (char *)malloc(sizeof(char) * len);
// 	if (after_dollar == NULL)
// 		exit(EXIT_FAILURE);
// 	*i += 1;
// 	j = 0;
// 	while (input[*i] && input[*i] != ' '
// 		&& input[*i] != '\n' && input[*i] != '$'
// 		&& input[*i] != '\"' && input[*i] != '\'')
// 	{
// 		after_dollar[j] = input[*i];
// 		j++;
// 		*i += 1;
// 	}
// 	after_dollar[j] = '\0';
// 	return (ft_strdup(getenv(after_dollar))); 
// }

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
			lexer(&main, input);
			print_lexems(&main);
		}
		// 3.parser part
		free(input);

		// 4.executor part
		// if no pipes
		// 	if builtin
		// 		call builtin
		// 	else
		//		fork
		// else
		//	if builtin {
		//		call builtin
		//		save result to tmp file
		//	}
		//	else
		//		common pipex
		// вообще надо создать нечто а-ля пайпекс с бонусами и положить в него проверку на билин или нет для случая с папами
	}
	// return (main->ret);
}
