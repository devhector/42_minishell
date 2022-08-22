/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:45:13 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/22 17:45:14 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	aux_print_scan(t_scan *scan)
{
	if (scan->error)
	{
		ft_putstr_fd("minisHell: ", 2);
		ft_putendl_fd(scan->error, 2);
	}
}

static void	aux_print_tmp(t_list *tmp)
{
	while (tmp)
	{
		aux_print_scan((t_scan *)tmp->content);
		tmp = tmp->next;
	}
}

void	print_error(t_shell *hell)
{
	t_list	*tmp;

	if (hell->error)
	{
		ft_putstr_fd("minisHell: ", STDERR_FILENO);
		ft_putendl_fd(hell->error, STDERR_FILENO);
		return ;
	}
	aux_print_tmp(hell->tokens);
	aux_print_tmp(hell->cmd);
	tmp = hell->cmd;
	while (tmp)
	{
		aux_print_tmp(((t_cmd *)tmp->content)->command);
		aux_print_tmp(((t_cmd *)tmp->content)->redirect);
		tmp = tmp->next;
	}
}

void	errno_handle(char *str, int errnb)
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
	g_exit_code = errnb;
}
