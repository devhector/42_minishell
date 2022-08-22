/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:46:28 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/22 17:46:29 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_elements(t_hash_elem **table)
{
	int			i;
	int			count;
	t_hash_elem	*elem;

	i = 0;
	count = 0;
	while (i < HASH_SIZE)
	{
		elem = table[i];
		while (elem)
		{
			count++;
			elem = elem->next;
		}
		i++;
	}
	return (count);
}

static char	*join_key_value(t_hash_elem *el)
{
	char	*key;
	char	*value;
	char	*tmp;
	char	*ret;

	key = ft_strdup(el->key);
	if (el->data)
	{
		value = ft_strdup(el->data);
		tmp = ft_strjoin(key, "=");
		ret = ft_strjoin(tmp, value);
		free(key);
		free(tmp);
		free(value);
	}
	else
		ret = key;
	return (ret);
}

char	**hash_env(t_shell *hell)
{
	int			i;
	int			count;
	char		**envp;
	t_hash_elem	**table;
	t_hash_elem	*elem;

	i = 0;
	count = 0;
	table = hell->env;
	envp = (char **)malloc(sizeof(char *) * (count_elements(hell->env) + 1));
	if (!envp)
		return (NULL);
	envp[count_elements(hell->env)] = NULL;
	while (i < HASH_SIZE)
	{
		elem = table[i];
		while (elem)
		{
			envp[count++] = join_key_value(elem);
			elem = elem->next;
		}
		i++;
	}
	return (envp);
}
