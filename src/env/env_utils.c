#include "minishell.h"

char	*get_value_env(t_hash_elem **envp, char *str)
{
	t_hash_elem	*elem;

	elem = table_lookup(envp, str);
	if (!elem)
		return (NULL);
	return (elem->data);
}

void	print_env(t_hash_elem **envp, t_cmd *cmd)
{
	t_hash_elem	*elem;
	t_hash_elem	*elems;

	elems = *envp;
	while (elems)
	{
		elem = elems;
		while (elem)
		{
			ft_putstr_fd(elem->key, cmd->fd_out);
			ft_putchar_fd('=', cmd->fd_out);
			ft_putendl_fd(elem->data, cmd->fd_out);
			elem = elem->next;
		}
		elems = elems->next;
	}
}

t_hash_elem		*create_elem(char *key, char *data)
{
	t_hash_elem	*elem;

	elem = malloc(sizeof(t_hash_elem));
	if (!elem)
		return (NULL);
	elem->key = ft_strdup(key);
	elem->data = ft_strdup(data);
	elem->next = NULL;
	return (elem);
}

int		update_env(t_hash_elem **env, char *key, char *value)
{
	t_hash_elem *elem;

	elem = table_lookup(env, key);
	if (!elem)
	{
		elem = create_elem(key, value);
		if (!elem)
		{
			ft_putendl_fd("Error: malloc failed", STDERR_FILENO);
			return (1);
		}
		insert_element(env, elem);
		clear_element(elem);
	}
	else
	{
		free(elem->data);
		elem->data = ft_strdup(value);
	}
	if (value)
		free(value);
	return (0);
}