#include "minishell.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		if ((str[i] == '+' || str[i] == '-') && !ft_isdigit(str[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_shell(t_shell *hell, int print)
{
	clean_shell(hell);
	if (print)
		ft_putendl_fd("exit", STDOUT_FILENO);
	exit(hell->exit_code);
}

int	b_exit(t_cmd *cmd, t_shell *hell)
{
	int		arg;
	char	**args;

	args = cmd->cmd_tab;
	if (!args[1])
		exit_shell(hell, 1);
	if (is_number(args[1]))
	{
		arg = ft_atoi(args[1]);
		if (arg >= 0 && arg <= 256)
			hell->exit_code = arg;
		else
			hell->exit_code = 127;
		exit_shell(hell, 1);
	}
	else
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("minisHell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		hell->exit_code = 2;
		exit_shell(hell, 0);
	}
	return (0);
}
