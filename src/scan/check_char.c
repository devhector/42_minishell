/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:46:03 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/22 17:46:04 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_redirect(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	is_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	has_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
			return (i);
		i++;
	}
	return (-1);
}
