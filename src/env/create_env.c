#include "minishell.h"

static char	*get_key(char	*data)
{
	char	*key;
	int		i;

	i = 0;
	while (data[i] && data[i] != '=')
		i++;
	key = ft_substr(data, 0, i);
	return (key);
}

static char	*get_value(char	*data)
{
	char	*value;
	int		i;

	i = 0;
	while (data[i] && data[i] != '=')
		i++;
	value = ft_substr(data, i + 1, ft_strlen(data));
	return (value);
}

static t_hash_elem	*create_elem(char	*data)
{
	t_hash_elem	*elem;

	elem = malloc(sizeof(t_hash_elem));
	if (!elem)
		return (NULL);
	elem->key = get_key(data);
	elem->data = get_value(data);
	elem->next = NULL;
	return (elem);
}

t_hash_elem	**create_table_env(char **envp)
{
	t_hash_elem	**table;
	t_hash_elem	*elem;
	int	i;

	i = 0;
	table = malloc(sizeof(t_hash_elem *) * HASH_SIZE);
	if (!table)
		return (NULL);
	init_table(table);
	while (envp[i])
	{
		elem = create_elem(envp[i]);
		insert_element(table, elem);
		clear_element(elem);
		i++;
	}
	return (table);
}
