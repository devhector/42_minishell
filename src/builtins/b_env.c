/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:47:50 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/23 14:27:05 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_putendl_fd(": run with no options or arguments", STDERR_FILENO);
		return (127);
	}
	return (0);
}
