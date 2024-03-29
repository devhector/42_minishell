/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:47:18 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/24 12:44:58 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap(t_scan *scan, char *token)
{
	free(scan->token);
	scan->token = token;
}

void	remove_quote_aux(t_scan *s, int i, int j)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(s->token, 0, i);
	tmp2 = ft_substr(s->token, i + 1, j);
	swap(s, ft_strjoin(tmp, tmp2));
	free(tmp);
	free(tmp2);
}

void	remove_quote(t_scan *scan)
{
	int		i;
	int		j;

	j = 0;
	i = has_quote(scan->token);
	if (i != -1)
	{
		j = has_quote(scan->token + i + 1);
		if (j != -1)
			remove_quote_aux(scan, i, j);
		else
			remove_quote_aux(scan, i, ft_strlen(scan->token));
	}
}

int	expanse(t_shell *hell)
{
	t_list	*tmp;
	t_list	*cmd;

	cmd = hell->cmd;
	while (cmd)
	{
		tmp = ((t_cmd *)cmd->content)->command;
		while (tmp)
		{
			if (token_expansor(tmp->content, hell))
				return (1);
			tmp = tmp->next;
		}
		tmp = ((t_cmd *)cmd->content)->redirect;
		while (tmp)
		{
			if (token_expansor(tmp->content, hell))
				return (1);
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
	return (command_table(hell));
}
