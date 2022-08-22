/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:45:58 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/22 18:24:10 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirections(t_scan *scan)
{
	char	*str;

	str = scan->token;
	if (str[0] == '>')
	{
		if (str[1] == '\0')
			return (0);
		else if (str[1] == '>' && !(str[2] == '\0' || str[2] == '|'))
		{
			scan->error = ft_strdup("syntax error redirect");
			g_exit_code = 1;
			return (1);
		}
	}
	else if (str[0] == '<' && !(str[1] == '<' || str[1] == '\0'))
	{
		scan->error = ft_strdup("syntax error redirect");
		g_exit_code = 1;
		return (1);
	}
	return (0);
}

int	check_tokens(t_shell *hell)
{
	t_list	*tmp;
	t_scan	*scan;

	tmp = hell->tokens;
	while (tmp)
	{
		scan = (t_scan *)tmp->content;
		if (check_quotes(scan))
			return ('q');
		if (check_redirections(scan))
			return ('r');
		if (check_backslash_semicolon(scan))
			return ('b');
		if (check_follow_pipe(tmp))
			return ('p');
		if (check_variable(tmp))
			return ('v');
		tmp = tmp->next;
	}
	return (0);
}
