/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:46:39 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/23 19:14:32 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child(t_cmd *cmd, t_shell *hell)
{
	handle_signals_child();
	if (cmd->fd_in > 2)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out > 2)
		dup2(cmd->fd_out, STDOUT_FILENO);
	close_all_fd(hell);
	if (is_bultin(cmd))
		exec_bultin(cmd, hell);
	else
	{
		execve(cmd->path, cmd->cmd_tab, hell->envp);
		errno_handle(cmd->cmd_tab[0], errno);
	}
	clear_table(hell->env);
	clean_shell(hell);
	rl_clear_history();
	exit(g_exit_code);
}

void	fork_child(t_cmd *cmd, t_shell *hell, int *pid)
{
	*pid = fork();
	if (*pid == 0)
		execute_child(cmd, hell);
	close_fd(cmd);
}

static int	check(t_cmd *cmd, t_shell *hell)
{
	char	*path;

	path = cmd->path;
	if (space_in_cmd(path, hell))
		return (1);
	if (check_path(cmd, hell))
		return (1);
	return (0);
}

int	execute_cmd(t_shell *hell, pid_t *pid, t_list *tmp, int i)
{
	handle_signals_parent();
	while (tmp)
	{
		((t_cmd *)tmp->content)->path = path(hell, ((t_cmd *)tmp->content));
		if (check(tmp->content, hell))
			return (1);
		if (builtin_parent(tmp->content, hell))
			fork_child((t_cmd *)tmp->content, hell, &pid[i++]);
		else
		{
			free(((t_cmd *)tmp->content)->path);
			((t_cmd *)tmp->content)->path = NULL;
			return (0);
		}
		free(((t_cmd *)tmp->content)->path);
		((t_cmd *)tmp->content)->path = NULL;
		tmp = tmp->next;
	}
	wait_pids(pid, i);
	return (0);
}

int	execute(t_shell *hell)
{
	pid_t	pid[420];

	if (hell->envp)
	{
		free_array(hell->envp);
		hell->envp = NULL;
	}
	hell->envp = hash_env(hell);
	if (open_pipes(hell))
		return (1);
	if (redirects(hell))
		return (1);
	if (execute_cmd(hell, pid, hell->cmd, 0))
		return (1);
	close_all_fd(hell);
	return (0);
}
