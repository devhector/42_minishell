/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:46:39 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/22 21:25:49 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	space_in_cmd(char *str, t_shell *hell)
{
	int		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i++]))
		{
			hell->error = ft_strjoin(str, " : no such file or directory");
			g_exit_code = 127;
			return (1);
		}
	}
	return (0);
}

int	execute_cmd(t_shell *hell, pid_t *pid, t_list *tmp)
{
	int	i;

	i = 0;
	tmp = hell->cmd;
	handle_signals_parent();
	while (tmp)
	{
		((t_cmd *)tmp->content)->path = path(hell, ((t_cmd *)tmp->content));
		if (space_in_cmd(((t_cmd *)tmp->content)->path, hell)
			|| check_path((t_cmd *)tmp->content, hell))
			return (1);
		if (builtin_parent(tmp->content, hell))
		{
			pid[i] = fork();
			if (pid[i++] == 0)
				execute_child((t_cmd *)tmp->content, hell);
			close_fd(tmp->content);
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
	t_list	*tmp;

	tmp = NULL;
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
	if (execute_cmd(hell, pid, tmp))
		return (1);
	close_all_fd(hell);
	return (0);
}
