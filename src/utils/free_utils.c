#include "minishell.h"

/*Function to free array of char*/
void	free_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	if (str)
		free(str);
	str = NULL;
}

void	del_scan(void *content)
{
	t_scan *scan;

	scan = (t_scan *)content;
	if (scan->token)
	{
		free(scan->token);
		scan->token = NULL;
	}
	if (scan->type)
	{
		free(scan->type);
		scan->type = NULL;
	}
	if (scan->error)
	{
		free(scan->error);
		scan->error = NULL;
	}
	free(scan);
	scan = NULL;
}

void	free_cmd (void *content)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	if (cmd->cmd_tab)
	{
		free_array(cmd->cmd_tab);
		cmd->cmd_tab = NULL;
	}
	tmp = cmd->command;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	tmp = cmd->redirect;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	free(cmd);
	cmd = NULL;
}
