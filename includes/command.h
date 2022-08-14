#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_cmd
{
	int		fd_in;
	int		fd_out;
	int		pipe[2];
	int		is_piped;
	char	*path;
	char	*error;
	char	**cmd_tab;
	t_list	*command;
	t_list	*redirect;
} t_cmd;

#endif