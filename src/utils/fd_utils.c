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
