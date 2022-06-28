#include "minishell.h"

void	minishell(char	**envp)
{

	char	*line;
	char	*cmdline;
	int		i;

	cmdline = NULL;

	while(42)
	{
		i = 0;
		line = readline(cmdline);
		printf("%s\n", line);
		if (!ft_strlen(line))
			break;
		while (envp[i])
			printf("%s\n", envp[i++]);
		free(cmdline);
	}
	free(line);
}