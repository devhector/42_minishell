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

	char	*cmdline;
	int		i;
	t_shell	hell;

	cmdline = NULL;
	hell.tokens = NULL;
	hell.lexems = NULL;

	// hell.env = create_table_env(envp);
	// print_table(hell.env);
	// clear_table(hell.env);
	(void)envp;

	while(42)
	{
		i = 0;
		hell.line = readline(cmdline);
		// printf("%s\n", hell.line);
		if (!ft_strlen(hell.line))
			break;
		tokenizer(&hell);
		free(cmdline);
	}
	free(hell.line);
}