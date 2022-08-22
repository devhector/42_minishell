/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:47:32 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/22 17:47:32 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_unset(t_cmd *cmd, t_shell *hell)
{
	int			i;
	t_hash_elem	*elem;

	i = 1;
	g_exit_code = 0;
	if (count_args(cmd->cmd_tab) == 1)
		return (0);
	while (cmd->cmd_tab[i])
	{
		elem = remove_element(hell->env, cmd->cmd_tab[i]);
		if (elem)
		{
			free(elem->key);
			if (elem->data)
				free(elem->data);
			free(elem);
		}
		i++;
	}
	return (0);
}
