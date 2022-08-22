/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:46:34 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/22 17:46:35 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_doc(char	*delimiter, int fd)
{
	char	*line;

	while (42)
	{
		line = readline("> ");
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		if (line)
			free(line);
	}
	close(fd);
	exit(0);
}

int	here_doc(char *delimiter)
{
	int	fd[2];
	int	pid;
	int	status;

	if (pipe(fd) == -1)
		return (-42);
	pid = fork();
	if (pid == -1)
		return (-42);
	if (pid == 0)
	{
		close(fd[0]);
		read_doc(delimiter, fd[1]);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	return (fd[0]);
}
