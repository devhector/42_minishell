#include "include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc < 1 || *argv)
	{
		printf("erro \n");
		return (1);
	}
	minishell(envp);
	return (0);
}