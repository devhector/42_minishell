#include "minishell.h"

void	print_error(t_shell *hell)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*tmp3;
	t_cmd	*cmd;
	t_scan	*scan;

	if (hell->error)
	{
		ft_putendl_fd(hell->error, STDOUT_FILENO);
		return ;
	}
	tmp = hell->tokens;
	while (tmp)
	{
		scan = (t_scan *)tmp->content;
		if (scan->error)
		{
			ft_putendl_fd(scan->error, STDOUT_FILENO);
			return ;
		}
		tmp = tmp->next;
	}
	tmp = hell->cmd;
	while (tmp)
	{
		cmd = tmp->content;
		if (cmd->error)
		{
			ft_putendl_fd(cmd->error, STDOUT_FILENO);
			return ;
		}
		tmp = tmp->next;
	}
	tmp = hell->cmd;
	while (tmp)
	{
		tmp2 = ((t_cmd *)tmp->content)->command;
		while (tmp2)
		{
			scan = tmp2->content;
			if (scan->error)
			{
				ft_putendl_fd(scan->error, STDOUT_FILENO);
				return ;
			}
			tmp2 = tmp2->next;
		}
		tmp3 = ((t_cmd *)tmp->content)->redirect;
		while (tmp3)
		{
			scan = tmp3->content;
			if (scan->error)
			{
				ft_putendl_fd(scan->error, STDOUT_FILENO);
				return ;
			}
			tmp3 = tmp3->next;
		}
		tmp = tmp->next;
	}
}