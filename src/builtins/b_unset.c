#include "minishell.h"

int	b_unset(t_cmd *cmd, t_shell *hell)
{
	int	i;
	t_hash_elem	*elem;

	i = 1;
	if (count_args(cmd->cmd_tab) == 1)
	{
		hell->exit_code = 0;
		return (0);
	}
	while (cmd->cmd_tab[i])
	{
		elem = remove_element(hell->env, cmd->cmd_tab[i]);
		if (elem)
		{
			free(elem->key);
			if (elem->data)
				free(elem->data);
			free(elem);
		}
		i++;
	}
	hell->exit_code = 0;
	return (0);
}
