/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:45:20 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/23 18:51:21 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_cmd *cmd)
{
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
}

void	close_fd_redirect(t_scan *redirect, t_cmd *cmd)
{
	if (!ft_strcmp(redirect->type, GREAT) || !ft_strcmp(redirect->type, DGREAT))
	{
		if (cmd->fd_out != -42)
			close(cmd->fd_out);
	}
	else if (!ft_strcmp(redirect->type, LESS)
		|| !ft_strcmp(redirect->type, DLESS))
	{
		if (cmd->fd_in != -42)
			close(cmd->fd_in);
	}
}

void	close_all_fd(t_shell *hell)
{
	t_list	*tmp;
	t_cmd	*cmd;

	tmp = hell->cmd;
	while (tmp)
	{
		cmd = (t_cmd *)tmp->content;
		close_fd(cmd);
		tmp = tmp->next;
	}
}
