#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc > 1 || argv[1])
	{
		printf("erro \n");
		return (1);
	}
	minishell(envp);
	return (0);
}