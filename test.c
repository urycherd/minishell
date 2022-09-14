#include <stdio.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	while(argv[++i])
		printf("%s\n", argv[i]);
}
