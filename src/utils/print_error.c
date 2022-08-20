#include "minishell.h"

void	aux_print_scan(t_scan *scan, t_shell *hell)
{
	if (scan->error)
	{
		ft_putstr_fd("minisHell: ", 2);
		ft_putendl_fd(scan->error, 2);
		hell->exit_code = scan->exit_code;
	}
}

void	aux_print_cmd(t_cmd *cmd, t_shell *hell)
{
	if (cmd->error)
	{
		ft_putstr_fd("minisHell: ", 2);
		ft_putendl_fd(cmd->error, 2);
		hell->exit_code = cmd->exit_code;
	}
}

void	aux_print_tmp(t_list *tmp, t_shell *hell)
{
	while (tmp)
	{
		aux_print_scan((t_scan *)tmp->content, hell);
		tmp = tmp->next;
	}
}

void	print_error(t_shell *hell)
{
	t_list	*tmp;

	if (hell->error)
	{
		ft_putendl_fd(hell->error, STDERR_FILENO);
		return ;
	}
	aux_print_tmp(hell->tokens, hell);
	aux_print_tmp(hell->cmd, hell);
	tmp = hell->cmd;
	while (tmp)
	{
		aux_print_tmp(((t_cmd *)tmp->content)->command, hell);
		aux_print_tmp(((t_cmd *)tmp->content)->redirect, hell);
		tmp = tmp->next;
	}
}

void	errno_handle(char *str, int errnb, t_shell *hell)
{
	if (errnb == EACCES)
	{
		ft_putstr_fd("minisHell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": permission denied", STDERR_FILENO);
	}
	else if (errnb == ENOENT)
	{
		ft_putstr_fd("minisHell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": no such file or directory", STDERR_FILENO);
	}
	else if (errnb == ENOTDIR)
	{
		ft_putstr_fd("minisHell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": Not a directory", STDERR_FILENO);
	}
	hell->exit_code = errnb;
}
