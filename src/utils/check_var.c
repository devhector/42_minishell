/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:03:40 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/26 21:22:21 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_exit_code(t_scan *s, char *first, int pos)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_itoa(g_exit_code);
	tmp2 = ft_strjoin(first, tmp);
	free(tmp);
	tmp = ft_substr(s->token, pos + 2, ft_strlen(s->token) - pos - 2);
	swap(s, ft_strjoin(tmp2, tmp));
	free(tmp);
	free(tmp2);
}

void	remove_str(t_scan *s, char *first, int pos)
{
	char	*tmp;

	tmp = ft_substr(s->token, pos, ft_strlen(s->token) - pos);
	swap(s, ft_strjoin(first, tmp));
	free(tmp);
}

void	remove_var(t_scan *s, int pos)
{
	int		i;
	char	*tmp;

	i = 1;
	tmp = ft_substr(s->token, 0, pos);
	if (s->token[pos + 1] == '?')
		put_exit_code(s, tmp, pos);
	else if (ft_isdigit(s->token[pos + 1]))
		remove_str(s, tmp, pos + 2);
	else
	{
		while (ft_isalnum(s->token[pos + i]) || s->token[pos + i] == '_')
			i++;
		remove_str(s, tmp, pos + i);
	}
	free(tmp);
}

void	check_var(t_scan *s)
{
	int	i;

	i = has_quote(s->token);
	if (i != -1)
		if (s->token[i] == '\'')
			return ;
	i = 0;
	if (s->token[i] == '$' && s->token[i + 1] == '\0')
	{
		free(s->token);
		s->token = ft_strdup("");
	}
	while (s->token[i])
	{
		if (s->token[i] == '$' && s->token[i + 1] != '"'
			&& s->token[i + 1] != '$' && s->token[i + 1] != '\0'
			&& s->token[i + 1] != ' ')
			remove_var(s, i);
		if (s->token[i] == '$' && s->token[i + 1] == '\0')
			i++;
		i++;
	}
}
