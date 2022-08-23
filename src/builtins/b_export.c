/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:47:39 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/23 14:07:30 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(str[i], STDOUT_FILENO);
		i++;
	}
	free_array(str);
}

int	check_name(char	*str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	create_var(char *str, t_shell *hell)
{
	char		*key;
	char		*value;

	if (check_name(str))
	{
		key = get_key(str);
		value = get_value(str);
		update_env(hell->env, key, value);
		free(key);
	}
	else
	{
		ft_putstr_fd("minisHell: export: `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("': is not a valid identifier", STDERR_FILENO);
	}
}

void	export(t_cmd *cmd, t_shell *hell)
{
	int		i;
	char	*key;

	i = 0;
	while (cmd->cmd_tab[++i])
	{
		if (ft_strchr(cmd->cmd_tab[i], '='))
			create_var(cmd->cmd_tab[i], hell);
		else
		{
			if (check_name(cmd->cmd_tab[i]))
			{
				key = ft_strdup(cmd->cmd_tab[i]);
				update_env(hell->env, key, NULL);
				free(key);
			}
			else
			{
				ft_putstr_fd("minisHell: export: `", STDERR_FILENO);
				ft_putstr_fd(cmd->cmd_tab[i], STDERR_FILENO);
				ft_putendl_fd("': is not a valid identifier", STDERR_FILENO);
			}
		}
	}
}

int	b_export(t_cmd *cmd, t_shell *hell)
{
	char	**args;

	args = cmd->cmd_tab;
	if (count_args(args) == 1)
	{
		print_env(sort_array(hell->envp));
		return (0);
	}
	else
		export(cmd, hell);
	return (0);
}
