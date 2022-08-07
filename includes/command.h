#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_cmd
{
	int		id;
	int		fd_in;
	int		fd_out;
	int		pipe_d;
	int		pipe[2];
	int		is_piped;
	char	**cmd_tab;
	char	*path;
	t_list	*command;
	t_list	*redirect;
} t_cmd;

#endif