/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:36:28 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/20 15:39:50 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_shell(t_shell *hell)
{
	if (hell->line)
		free(hell->line);
	if (hell->error)
		free(hell->error);
	if (hell->tokens)
		ft_lstclear(&hell->tokens, del_scan);
	if (hell->cmd)
		ft_lstclear(&hell->cmd, free_cmd);
	if (hell->envp)
	{
		free_array(hell->envp);
		hell->envp = NULL;
	}
	hell->line = NULL;
	hell->error = NULL;
	hell->tokens = NULL;
	hell->cmd = NULL;
}
