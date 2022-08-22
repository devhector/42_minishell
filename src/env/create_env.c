/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:47:00 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/22 17:47:01 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char	*data)
{
	char	*key;
	int		i;

	i = 0;
	while (data[i] && data[i] != '=')
		i++;
	key = ft_substr(data, 0, i);
	return (key);
}

char	*get_value(char	*data)
{
	char	*value;
	int		i;

	i = 0;
	while (data[i] && data[i] != '=')
		i++;
	if (!data[i + 1])
		return (NULL);
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
	int			i;
	t_hash_elem	**table;
	t_hash_elem	*elem;

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
