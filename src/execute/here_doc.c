/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:46:34 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/25 18:29:53 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	s_read_doc(int signal, void *hell)
{
	static t_shell	*hellish = NULL;

	if (!hellish)
		hellish = (t_shell *)hell;
	if (signal == SIGINT)
	{
		g_exit_code = 128 + signal;
		ft_putstr_fd("\n", STDOUT_FILENO);
		clean_shell(hellish);
		clear_table(hellish->env);
		rl_clear_history();
		rl_replace_line("", 0);
		rl_on_new_line();
		exit(g_exit_code);
	}
	return (0);
}

void	signal_here_doc(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_read_doc(t_shell *hell)
{
	signal(SIGINT, (void (*)(int))s_read_doc);
	s_read_doc(0, hell);
	signal(SIGQUIT, SIG_IGN);
}

void	read_doc(char	*delimiter, int fd, t_shell *hell)
{
	char	*line;

	signal_read_doc(hell);
	while (42)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minisHell: here-doc: EOF\n", STDERR_FILENO);
			break ;
		}
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
	clear_table(hell->env);
	clean_shell(hell);
	rl_clear_history();
	exit(0);
}

int	here_doc(char *delimiter, t_shell *hell)
{
	int	fd[2];
	int	pid;
	int	status;

	g_exit_code = 0;
	if (pipe(fd) == -1)
		return (-43);
	pid = fork();
	if (pid == -1)
		return (-43);
	if (pid == 0)
	{
		close(fd[0]);
		read_doc(delimiter, fd[1], hell);
	}
	signal_here_doc();
	close(fd[1]);
	waitpid(pid, &status, 0);
	return (fd[0]);
}
