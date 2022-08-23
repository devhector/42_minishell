/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:42:18 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/23 13:52:25 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *hell, char **envp)
{
	hell->cmd = NULL;
	hell->envp = NULL;
	hell->line = NULL;
	hell->error = NULL;
	hell->tokens = NULL;
	hell->env = create_table_env(envp);
}

int	full_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	minishell(char	**envp)
{
	t_shell	hell;

	init_shell(&hell, envp);
	while (42)
	{
		handle_signals();
		clean_shell(&hell);
		hell.line = readline("$> ");
		add_history(hell.line);
		if (!hell.line)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (!*hell.line || full_space(hell.line))
			continue ;
		if (scan(&hell) || execute(&hell))
		{
			print_error(&hell);
			continue ;
		}
	}
	clear_table(hell.env);
	rl_clear_history();
}
