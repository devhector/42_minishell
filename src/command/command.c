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

int	command(t_shell *hell)
{
	int		id;
	t_cmd	*cmd;
	t_list	*token;

	id = 0;
	token = hell->tokens;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
		if (!cmd)
			return (1);
	cmd->command = NULL;
	cmd->redirect = NULL;
	while (token)
	{
		if (!ft_strcmp(((t_scan *)token->content)->type, PIPE))
			break ;
		add_cmd(token, cmd);
		token = token->next;
	}
	ft_lstadd_back(&hell->cmd, ft_lstnew(cmd));
	return (0);
}