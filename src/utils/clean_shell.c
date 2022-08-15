#include "minishell.h"

void clean_shell(t_shell *hell)
{
	if (hell->line)
		free(hell->line);
	if (hell->error)
		free(hell->error);
	if (hell->tokens)
		ft_lstclear(&hell->tokens, del_scan);
	if (hell->cmd)
		ft_lstclear(&hell->cmd, free_cmd);
	if (hell->envp)
	{
		free_array(hell->envp);
		hell->envp = NULL;
	}
	hell->line = NULL;
	hell->error = NULL;
	hell->tokens = NULL;
	hell->cmd = NULL;
}