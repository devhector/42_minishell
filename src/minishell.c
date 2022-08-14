#include "minishell.h"

void init_shell(t_shell *hell, char **envp)
{
	hell->cmd = NULL;
	hell->envp = NULL;
	hell->line = NULL;
	hell->error = NULL;
	hell->tokens = NULL;
	hell->env = create_table_env(envp);
}

void	minishell(char	**envp)
{
	t_shell	hell;

	init_shell(&hell, envp);
	while (42)
	{
		hell.line = readline("$> ");
		add_history(hell.line);
		if (!ft_strlen(hell.line))
		{
			if (hell.line)
				free(hell.line);
			hell.line = NULL;
			break ;
		}
		if (scan(&hell))
		{
			printf("error: scan\n");
			free(hell.line);
			hell.line = NULL;
			continue;
		}
		execute(&hell);
		free(hell.line);
		hell.line = NULL;
		if (hell.error)
		{
			free(hell.error);
			hell.error = NULL;
		}
		if (hell.tokens)
			ft_lstclear(&hell.tokens, del_scan);
		if (hell.cmd)
			ft_lstclear(&hell.cmd, free_cmd);
		if (hell.envp)
		{
			free_array(hell.envp);
			hell.envp = NULL;
		}
	}
	clear_table(hell.env);
}