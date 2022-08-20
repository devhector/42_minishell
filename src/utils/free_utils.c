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

static void	free_cmd_aux(t_list *tmp)
{
	t_list	*tmp2;

	while(tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

void	free_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	if (cmd->cmd_tab)
		free_array(cmd->cmd_tab);
	if (cmd->path)
	{
		free(cmd->path);
		cmd->path = NULL;
	}
	if (cmd->error)
	{
		free(cmd->error);
		cmd->error = NULL;
	}
	free_cmd_aux(cmd->command);
	free_cmd_aux(cmd->redirect);
	free(cmd);
	cmd = NULL;
}
