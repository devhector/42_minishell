#include "include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

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
	return (0);
}