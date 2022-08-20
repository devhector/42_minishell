#include "minishell.h"

static int	error_message(char *str)
{
	ft_putstr_fd("minisHell: cd: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	return (1);
}

static int	cd_home(t_shell *hell)
{
	char	*home;

	home = get_value_env(hell->env, "HOME");
	if (!home)
	{
		ft_putendl_fd("minisHell: cd: HOME not set", STDERR_FILENO);
		return (1);
	}
	if (chdir(home) == -1)
		return (error_message(home));
	return (0);
}

int	cd_path(char *str, t_shell *hell)
{
	char	*old;
	char	*new;

	old = get_value_env(hell->env, "OLDPWD");
	new = getcwd(NULL, 0);
	if (!new)
	{
		ft_putendl_fd("minisHell: cd: Current directory not found", \
				STDERR_FILENO);
		return (1);
	}
	if (str[0] == '-' && str[1] == '\0')
	{
		if (chdir(old) == -1)
			return (error_message(old));
		update_env(hell->env, "PWD", old);
	}
	else
	{
		if (chdir(str) == -1)
			return (error_message(str));
		update_env(hell->env, "PWD", getcwd(NULL, 0));
	}
	update_env(hell->env, "OLDPWD", new);
	return (0);
}

int	b_cd(t_cmd *cmd, t_shell *hell)
{
	if (count_args(cmd->cmd_tab) == 1)
		return (cd_home(hell));
	else if (count_args(cmd->cmd_tab) == 2)
		return (cd_path(cmd->cmd_tab[1], hell));
	else
	{
		ft_putendl_fd("minisHell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
}
