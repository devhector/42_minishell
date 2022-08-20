#include "minishell.h"

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

void	exec_bultin(t_cmd *cmd, t_shell *hell)
{
	char	*str;

	str = cmd->cmd_tab[0];
	if (!ft_strcmp(str, "echo\0"))
		hell->exit_code = b_echo(cmd);
	else if (!ft_strcmp(str, "env\0"))
		hell->exit_code = b_env(cmd, hell);
	else if (!ft_strcmp(str, "pwd\0"))
		b_pwd(hell);
}

void	execute_child(t_cmd *cmd, t_shell *hell)
{
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
		errno_handle(cmd->cmd_tab[0], errno, hell);
	}
	clear_table(hell->env);
	clean_shell(hell);
	rl_clear_history();
	exit(hell->exit_code);
}

void	wait_pids(pid_t *pid, int i, t_shell *hell)
{
	int	status;
	int	j;

	j = 0;
	status = 0;
	while (j < i)
	{
		waitpid(pid[j], &status, 0);
		j++;
	}
	if (WIFEXITED(status))
		hell->exit_code = WEXITSTATUS(status);
}

int	space_in_cmd(char *str, t_shell *hell)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i++]))
		{
			hell->error = ft_strjoin("No such file or directory: ", str);
			hell->exit_code = 1;
			return (1);
		}
	}
	return (0);
}

int	check_path(t_cmd *cmd, t_shell *hell)
{
	char	*tmp;

	if (!cmd->path)
	{
		tmp = ft_strjoin("minisHell: ", cmd->cmd_tab[0]);
		hell->error = ft_strjoin(tmp, " : Command not found");
		hell->exit_code = 127;
		free(tmp);
		return (1);
	}
	if (is_bultin(cmd))
		return (0);
	else if (access(cmd->path, F_OK | X_OK) == -1)
	{
		tmp = ft_strjoin("minisHell: ", cmd->cmd_tab[0]);
		hell->error = ft_strjoin(tmp, " : Command not found");
		hell->exit_code = 127;
		free(tmp);
		return (1);
	}
	return (0);
}

int	builtin_parent(t_cmd *cmd, t_shell *hell)
{
	char	*str;

	str = cmd->cmd_tab[0];
	if (!ft_strcmp(str, "cd\0"))
	{
		hell->exit_code = b_cd(cmd, hell);
		return (0);
	}
	if (!ft_strcmp(str, "exit\0"))
		return (b_exit(cmd, hell));
	if (!ft_strcmp(str, "export\0"))
		return (b_export(cmd, hell));
	if (!ft_strcmp(str, "unset\0"))
		return (b_unset(cmd, hell));

	return (1);
}

int	execute_cmd(t_shell *hell, pid_t *pid, t_list *tmp)
{
	int	i;

	i = 0;
	tmp = hell->cmd;
	while (tmp)
	{
		((t_cmd *)tmp->content)->path = path(hell, ((t_cmd *)tmp->content));
		if (space_in_cmd(((t_cmd *)tmp->content)->path, hell)
			|| check_path((t_cmd *)tmp->content, hell))
			return (1);
		if (builtin_parent(tmp->content, hell) /*&& ((t_cmd *)tmp->content)->path*/)
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
	wait_pids(pid, i, hell);
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
