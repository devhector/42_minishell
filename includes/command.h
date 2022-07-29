#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_cmd
{
	int		id;
	int		fd_in;
	int		fd_out;
	int		pipe[2];
	int		is_piped;
	char	**commands;
	t_list	*command;
	t_list	*redirect;
} t_cmd;


#endif