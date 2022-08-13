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
	if (cmd->fd_in > 2)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out > 2)
		dup2(cmd->fd_out, STDOUT_FILENO);
	close_all_fd(hell);
	if (execve(cmd->path, cmd->cmd_tab, hell->envp) == -1)
	{
		hell->error = ft_strdup("execve error");
	}
}

void	wait_pids(pid_t *pid, int i)
{
	int	status;
	int	j;

	j = 0;
	while (j < i)
	{
		waitpid(pid[j], &status, 0);
		j++;
	}
}

int	space_in_cmd(char *str, t_shell *hell)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i++]))
		{
			hell->error = ft_strjoin(str, " : No such file or directory");
			return (1);
		}
	}
	return (0);
}

int	is_path_ok(char *str, t_shell *hell)
{
	if (access(str, F_OK) == -1)
	{
		hell->error = ft_strjoin(str, " : No such file or directory");
		return (1);
	}
	return (0);
}

int	execute_cmd(t_shell *hell, pid_t *pid, t_list *tmp)
{
	int		i;

	i = 0;
	tmp = hell->cmd;
	while (tmp)
	{
		if (space_in_cmd(((t_cmd *)tmp->content)->cmd_tab[0], hell))
			return (1);
		((t_cmd *)tmp->content)->path = path(hell, ((t_cmd *)tmp->content));
		if (((t_cmd *)tmp->content)->path
			&& !is_path_ok(((t_cmd *)tmp->content)->path, hell))
		{
			pid[i] = fork();
			if (pid[i] == 0)
				execute_child(((t_cmd *)tmp->content), hell);
			i++;
			close_fd(tmp->content);
		}
		else
			return (1);
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
		free_array(hell->envp);
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
