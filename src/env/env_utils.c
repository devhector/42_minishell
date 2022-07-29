#include "minishell.h"

char	*get_value_env(t_hash_elem **envp, char *str)
{
	t_hash_elem	*elem;

	elem = table_lookup(envp, str);
	if (!elem)
		return (NULL);
	return (elem->data);
}