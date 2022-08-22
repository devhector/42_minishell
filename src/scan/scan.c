/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:45:45 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/22 18:35:11 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_all(t_shell *hell)
{
	if (check_tokens(hell))
		return (1);
	if (lexer(hell))
		return (1);
	if (syntax(hell))
		return (1);
	if (command(hell))
		return (1);
	return (0);
}

int	scan(t_shell *hell)
{
	int		i;
	int		start;
	char	*line;

	i = 0;
	line = hell->line;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (is_quote(line[i]))
			quote_token(hell, &i);
		else if (is_redirect(line[i]))
			redirect_token(hell, &i);
		else
		{
			start = i;
			while (line[i] && !ft_isspace(line[i]) && !is_redirect(line[i])
				&& !is_quote(line[i]))
				i++;
			create_token(hell, start, i);
		}
	}
	return (check_all(hell));
}
