/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:45:52 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/24 08:43:18 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(t_scan *scan)
{
	int		i;
	int		pos;
	char	*str;

	i = 0;
	str = scan->token;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			pos = i++;
			while (str[i] && str[i] != str[pos])
				i++;
			if (str[i] == '\0')
			{
				scan->error = ft_strdup("unclosed quote");
				g_exit_code = 1;
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_backslash_semicolon(t_scan *scan)
{
	int		i;
	int		is_quotes;
	char	*str;

	i = 0;
	is_quotes = 0;
	str = scan->token;
	while (str[i])
	{
		if (is_quote(str[i]))
			is_quotes = !is_quotes;
		if ((str[i] == '\\' || str[i] == ';') && !is_quotes)
		{
			scan->error = ft_strjoin("syntax error: ", str);
			g_exit_code = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_follow_pipe(t_list *token)
{
	t_list	*next;
	t_scan	*scan;
	t_scan	*scan_next;

	if (token->next == NULL)
		return (0);
	next = token->next;
	scan = (t_scan *)token->content;
	scan_next = (t_scan *)next->content;
	if (scan->token[0] == '|' && scan_next->token[0] == '|')
	{
		scan->error = ft_strdup("syntax error pipe");
		g_exit_code = 1;
		return (1);
	}
	return (0);
}

int	check_path(t_cmd *cmd, t_shell *hell)
{
	if (is_bultin(cmd))
		return (0);
	if (!cmd->path)
	{
		hell->error = ft_strjoin(cmd->cmd_tab[0], " : Command not found");
		g_exit_code = 127;
		return (1);
	}
	else if (access(cmd->path, F_OK | X_OK) == -1)
	{
		hell->error = ft_strjoin(cmd->cmd_tab[0], " : Command not found");
		g_exit_code = 127;
		return (1);
	}
	return (0);
}
