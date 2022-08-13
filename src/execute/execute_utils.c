#include "minishell.h"

int	open_pipes(t_shell *hell)
{
	t_cmd	*cmd;
	t_cmd	*cmd_n;
	t_list	*tmp;

	tmp = hell->cmd;
	while (tmp)
	{
		cmd = (t_cmd *)tmp->content;
		if (cmd->is_piped)
		{
			cmd_n = (t_cmd *)tmp->next->content;
			if (pipe(cmd->pipe) == -1)
			{
				hell->error = ft_strdup("pipe error");
				return (1);
			}
			cmd->pipe_d = 1;
			cmd_n->pipe_d = 1;
			cmd->fd_out = cmd->pipe[1];
			cmd_n->fd_in = cmd->pipe[0];
		}
		tmp = tmp->next;
	}
	return (0);
}

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

void	open_file(t_list *redirect, t_cmd *cmd)
{
	t_scan	*scan;
	t_scan	*scan_n;

	scan = (t_scan *)redirect->content;
	close_fd_redirect(scan, cmd);
	scan_n = (t_scan *)redirect->next->content;
	if (!ft_strcmp(scan->type, GREAT))
		cmd->fd_out = open(scan_n->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strcmp(scan->type, DGREAT))
		cmd->fd_out = open(scan_n->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (!ft_strcmp(scan->type, LESS))
		cmd->fd_in = open(scan_n->token, O_RDONLY);
	else if (!ft_strcmp(scan->type, DLESS))
		cmd->fd_in = here_doc(scan_n->token);
}

int	redirects(t_shell *hell)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = hell->cmd;
	while (tmp)
	{
		tmp2 = ((t_cmd *)tmp->content)->redirect;
		while (tmp2)
		{
			open_file(tmp2, (t_cmd *)tmp->content);
			tmp2 = tmp2->next->next;
		}
		if (((t_cmd *)tmp->content)->fd_in == -42)
			((t_cmd *)tmp->content)->fd_in = STDIN_FILENO;
		if (((t_cmd *)tmp->content)->fd_out == -42)
			((t_cmd *)tmp->content)->fd_out = STDOUT_FILENO;
		tmp = tmp->next;
	}
	return (0);
}

char	*path(t_shell *hell, t_cmd *cmd)
{
	char	**path_env;
	int		i;
	char	*tmp;
	char	*cmd_s;

	i = 0;
	if (ft_strchr(cmd->cmd_tab[0], '/'))
		return (ft_strdup(cmd->cmd_tab[0]));
	path_env = ft_split(get_value_env(hell->env, "PATH"), ':');
	while (path_env[i])
	{
		tmp = ft_strjoin(path_env[i], "/");
		cmd_s = ft_strjoin(tmp, cmd->cmd_tab[0]);
		if (access(cmd_s, X_OK) == 0)
		{
			free(tmp);
			free_array(path_env);
			return (cmd_s);
		}
		free(tmp);
		free(cmd_s);
		i++;
	}
	free_array(path_env);
	return (NULL);
}
