#include "minishell.h"

void print_node(t_hash_elem *node)
{
	t_hash_elem	*prev;

	while (node)
	{
		prev = node;
		node = node->next;
		printf("%s=%s\n", prev->key, prev->data);
	}
}

void print_table(t_hash_elem **table)
{
	int	i;

	i = 0;
	while (i < HASH_SIZE)
	{
		printf("%d -\n", i);
		print_node(table[i]);
		i++;
	}
}

void	minishell(char	**envp)
{

	// char	*cmdline;
	int		i;
	t_shell	hell;

	// cmdline = NULL;
	hell.tokens = NULL;
	hell.cmd = NULL;
	hell.error = NULL;
	hell.envp = NULL;

	hell.env = create_table_env(envp);

	(void)envp;

	while (42)
	{
		i = 0;
		hell.line = readline("$> ");
		// printf("%s\n", hell.line);
		if (!ft_strlen(hell.line))
		{
			if (hell.line)
				free(hell.line);
			// free(cmdline);
			hell.line = NULL;
			// cmdline = NULL;
			break ;
		}
		if (scan(&hell))
		{
			printf("error: scan\n");
			free(hell.line);
			// free(cmdline);
			continue;
		}
		execute(&hell);
		free(hell.line);
		if (hell.error)
			free(hell.error);
		// free(cmdline);
		ft_lstclear(&hell.tokens, del_scan);
		ft_lstclear(&hell.cmd, free_cmd);
	}
	clear_table(hell.env);
	free_array(hell.envp);
}