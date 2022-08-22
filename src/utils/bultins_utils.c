/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:36:17 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/22 11:04:09 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	builtin_parent(t_cmd *cmd, t_shell *hell)
{
	char	*str;

	str = cmd->cmd_tab[0];
	if (!ft_strcmp(str, "cd\0"))
	{
		g_exit_code = b_cd(cmd, hell);
		return (0);
	}
	if (!ft_strcmp(str, "exit\0"))
		return (b_exit(cmd, hell));
	if (!ft_strcmp(str, "export\0"))
		return (b_export(cmd, hell));
	if (!ft_strcmp(str, "unset\0"))
		return (b_unset(cmd, hell));
	return (1);
}

void	exec_bultin(t_cmd *cmd, t_shell *hell)
{
	char	*str;

	str = cmd->cmd_tab[0];
	if (!ft_strcmp(str, "echo\0"))
		g_exit_code = b_echo(cmd);
	else if (!ft_strcmp(str, "env\0"))
		g_exit_code = b_env(cmd, hell);
	else if (!ft_strcmp(str, "pwd\0"))
		b_pwd();
}

void	wait_pids(pid_t *pid, int i)
{
	int	status;
	int	j;

	j = 0;
	status = 0;
	while (j < i)
	{
		waitpid(pid[j], &status, 0);
		j++;
	}
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
}
