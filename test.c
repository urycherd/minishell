#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	// int	i;

	// i = 0;
	// while(argv[++i])
	// 	printf("%s\n", argv[i]);

	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * 10);
	i = 0;
	while (i < 10)
	{
		str[i] = i + '0';
		i++;
	}
	printf("%s\n", str);
	printf("%s\n", &str[4]);
}

// **************************** TRASH ******************************

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
//	
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

// void	old_lexer(t_main **main, char *input)
// {
// 	char	**words;
//
// 	add_history(input);
// 	// while (*input && *input != '\n')
// 	// {
// 	// 	skip_spaces(&input);
// 	// 	get_word(&input);
// 	// }
// 	change_to_spaces(&input);
// 	words = ft_split(input, ' ');
// 	while(*words)
// 	{
// 		printf("%s\n", *words);
// 		words++;
// 	}
// }