#include "hash_table.h"

void	init_table(t_hash_elem **table)
{
	int	i;

	i = 0;
	while (i < HASH_SIZE)
	{
		table[i] = NULL;
		i++;
	}
}

void	clear_element(t_hash_elem *elem)
{
	free(elem->key);
	free(elem->data);
	if (elem)
		free(elem);
	elem = NULL;
}

void	clear_node(t_hash_elem *node)
{
	t_hash_elem	*prev;

	while (node)
	{
		prev = node;
		node = node->next;
		clear_element(prev);
	}
}

void	clear_table(t_hash_elem **table)
{
	int	i;

	i = 0;
	while (i < HASH_SIZE)
		clear_node(table[i++]);
	if (table)
		free(table);
}
