#include "minishell.h"

int	is_bultin(t_cmd *cmd)
{
	char	*str;

	str = cmd->cmd_tab[0];
	if (!ft_strcmp(str, "echo\0"))
		return (1);
	if (!ft_strcmp(str, "cd\0"))
		return (1);
	if (!ft_strcmp(str, "pwd\0"))
		return (1);
	if (!ft_strcmp(str, "export\0"))
		return (1);
	if (!ft_strcmp(str, "unset\0"))
		return (1);
	if (!ft_strcmp(str, "env\0"))
		return (1);
	if (!ft_strcmp(str, "exit\0"))
		return (1);
	return (0);
}