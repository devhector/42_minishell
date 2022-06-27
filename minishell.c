#include "include/minishell.h"

void	minishell(char	**envp)
{

	char	*line;
	char	*cmdline;

	cmdline = NULL;

	while(42)
	{
		line = readline(cmdline);
		printf("%s\n", line);
		if (!ft_strlen(line))
			break;
		free(cmdline);
	}
	free(line);
}