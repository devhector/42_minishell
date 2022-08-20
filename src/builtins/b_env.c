#include "minishell.h"

int	b_env(t_cmd *cmd, t_shell *hell)
{
	int	i;

	if (count_args(cmd->cmd_tab) == 1)
	{
		if (!table_lookup(hell->env, "PATH"))
		{
			ft_putstr_fd("minishell: env: ", STDERR_FILENO);
			ft_putendl_fd(": no such file or directory", STDERR_FILENO);
			return (127);
		}
		i = 0;
		while (hell->envp[i])
		{
			ft_putendl_fd(hell->envp[i], STDOUT_FILENO);
			i++;
		}
	}
	else
	{
		ft_putstr_fd("minishell: env: ", STDERR_FILENO);
		ft_putstr_fd(cmd->cmd_tab[1], STDERR_FILENO);
		ft_putendl_fd(": no such file or directory", STDERR_FILENO);
		return (127);
	}
	return (0);
}