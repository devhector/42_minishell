/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:45:35 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/25 18:58:56 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_syntax(t_list *token)
{
	t_scan	*scan;

	scan = (t_scan *)token->content;
	if (!ft_strcmp(scan->type, "PIPE"))
	{
		if (!token->prev || !token->next)
		{
			scan->error = ft_strdup("PIPE: syntax error");
			g_exit_code = 1;
			return (1);
		}
	}
	return (0);
}

int	is_redirect_str(char *type)
{
	if (!ft_strcmp(type, LESS) || !ft_strcmp(type, GREAT)
		|| !ft_strcmp(type, DLESS) || !ft_strcmp(type, DGREAT))
		return (1);
	return (0);
}

int	redirect_syntax(t_list *token)
{
	t_list	*next;
	t_scan	*scan;
	t_scan	*next_scan;

	scan = (t_scan *)token->content;
	if (is_redirect_str(scan->type))
	{
		next = token->next;
		if (!next)
		{
			scan->error = ft_strjoin(scan->type, ": syntax error redirect");
			g_exit_code = 1;
			return (1);
		}
		next_scan = (t_scan *)next->content;
		if (ft_strcmp(next_scan->type, WORD)
			&& ft_strcmp(next_scan->type, ASSIGNMENT))
		{
			scan->error = \
			ft_strjoin(next_scan->type, ": syntax error redirect");
			g_exit_code = 1;
			return (1);
		}
	}
	return (0);
}

int	parentesis_syntax(t_list *token)
{
	int		i;
	t_scan	*scan;

	i = 0;
	scan = (t_scan *)token->content;
	while (scan->token[i])
	{
		if ((scan->token[i] == '(' || scan->token[i] == ')')
			&& has_quote(scan->token) == -1)
		{
			scan->error = ft_strdup(" syntax error parentesis");
			g_exit_code = 2;
			return (1);
		}
		i++;
	}
	return (0);
}

int	syntax(t_shell *hell)
{
	t_list	*token;

	token = hell->tokens;
	while (token)
	{
		if (pipe_syntax(token))
			return (1);
		if (redirect_syntax(token))
			return (1);
		if (parentesis_syntax(token))
			return (1);
		token = token->next;
	}
	return (0);
}
