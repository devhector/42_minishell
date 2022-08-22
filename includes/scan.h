/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:33:36 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/20 14:33:38 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAN_H
# define SCAN_H

typedef struct s_scan
{
	char	*token;
	char	*type;
	char	*error;
	int		exit_code;
}	t_scan;

int	is_quote(char c);
int	is_redirect(char c);
int	is_separator(char c);
int	has_quote(char *str);

#endif