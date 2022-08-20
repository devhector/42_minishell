#include "minishell.h"

int	b_echo(t_cmd *cmd)
{
	int		i;
	char	**cmd_tab;
	char	end;

	i = 1;
	cmd_tab = cmd->cmd_tab;
	end = '\n';
	if (cmd_tab[i] && !ft_strcmp(cmd_tab[i], "-n"))
	{
		i++;
		end = '\0';
	}
	while (cmd_tab[i])
	{
		ft_putstr_fd(cmd_tab[i], STDOUT_FILENO);
		if (cmd_tab[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	ft_putchar_fd(end, STDOUT_FILENO);
	return (0);
}
