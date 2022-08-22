/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:30:20 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/22 17:30:21 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_cmd
{
	int		fd_in;
	int		fd_out;
	int		pipe[2];
	int		is_piped;
	int		exit_code;
	char	*path;
	char	*error;
	char	**cmd_tab;
	t_list	*command;
	t_list	*redirect;
}	t_cmd;

#endif