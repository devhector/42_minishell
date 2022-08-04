#include "minishell.h"

void	add_cmd(t_list *token, t_cmd *cmd)
{
	t_scan	*s;
	t_scan	*s_prev;

	s = (t_scan *)token->content;
	if (token->prev)
	{
		s_prev = (t_scan *)token->prev->content;
		if (is_redirect_str(s->type) || is_redirect_str(s_prev->type))
			ft_lstadd_back(&cmd->redirect, ft_lstnew(s));
		else
			ft_lstadd_back(&cmd->command, ft_lstnew(s));
	}
	else
	{
		if (is_redirect_str(s->type))
			ft_lstadd_back(&cmd->redirect, ft_lstnew(s));
		else
			ft_lstadd_back(&cmd->command, ft_lstnew(s));
	}
}

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->id = -42;
	cmd->fd_in = -42;
	cmd->fd_out = -42;
	cmd->is_piped = -42;
	cmd->cmd_tab = NULL;
	cmd->command = NULL;
	cmd->redirect = NULL;
	return (cmd);
}

int	command(t_shell *hell)
{
	int		id;
	t_cmd	*cmd;
	t_list	*token;

	id = 0;
	token = hell->tokens;
	cmd = create_cmd();
	while (token)
	{
		if (!ft_strcmp(((t_scan *)token->content)->type, PIPE))
		{
			cmd->id = id++;
			cmd->is_piped = 1;
			ft_lstadd_back(&hell->cmd, ft_lstnew(cmd));
			cmd = create_cmd();
			cmd->is_piped = 1;
		}
		else
			add_cmd(token, cmd);
		if (cmd->id == -42)
			cmd->id = id++;
		token = token->next;
	}
	ft_lstadd_back(&hell->cmd, ft_lstnew(cmd));
	return (expanse(hell));
}