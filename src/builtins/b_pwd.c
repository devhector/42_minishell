#include "minishell.h"

int	b_pwd(t_shell *hell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		free(pwd);
	}
	else
	{
		ft_putendl_fd("minisHell: pwd: no such file or directory", \
			STDERR_FILENO);
		hell->exit_code = 1;
	}
	hell->exit_code = 0;
	return (0);
}
