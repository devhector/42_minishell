/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:46:24 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/22 17:46:24 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	hash(const char *key)
{
	int	hash;

	hash = 0;
	while (*key)
	{
		hash += *key;
		hash = (hash * (*key)) % HASH_SIZE;
		key++;
	}
	return (hash);
}

t_hash_elem	*table_lookup(t_hash_elem **table, const char *key)
{
	t_hash_elem	*elem;

	elem = table[hash(key)];
	while (elem)
	{
		if (!ft_strncmp(elem->key, key, ft_strlen(elem->key)))
			return (elem);
		elem = elem->next;
	}
	return (NULL);
}

void	insert_element(t_hash_elem **table, t_hash_elem *elem)
{
	t_hash_elem	*new_elem;

	new_elem = table_lookup(table, elem->key);
	if (new_elem)
	{
		free(new_elem->data);
		new_elem->data = ft_strdup(elem->data);
	}
	else
	{
		new_elem = malloc(sizeof(t_hash_elem));
		if (!new_elem)
			return ;
		new_elem->key = ft_strdup(elem->key);
		new_elem->data = ft_strdup(elem->data);
		new_elem->next = table[hash(elem->key)];
		table[hash(elem->key)] = new_elem;
	}
}

t_hash_elem	*remove_element(t_hash_elem **table, const char *key)
{
	t_hash_elem	*elem;
	t_hash_elem	*prev;

	elem = table_lookup(table, key);
	if (!elem)
		return (NULL);
	prev = table[hash(key)];
	if (prev == elem)
	{
		table[hash(key)] = elem->next;
		return (elem);
	}
	else
	{
		while (prev->next != elem && prev->next)
			prev = prev->next;
		prev->next = elem->next;
		return (elem);
	}
	return (NULL);
}
