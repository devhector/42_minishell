/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:46:50 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/22 17:51:32 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ctrl_c(int signal)
{
	g_exit_code = 128 + signal;
	return ;
}

static void	ctrl_d(int signal)
{
	(void)signal;
	g_exit_code = 0;
	return ;
}

static void	parent(int signal)
{
	g_exit_code = 128 + signal;
	ft_putendl_fd("", STDOUT_FILENO);
	return ;
}

void	handle_signals_child(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_d);
}

void	handle_signals_parent(void)
{
	signal(SIGINT, parent);
	signal(SIGQUIT, parent);
}
