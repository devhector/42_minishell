#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_cmd
{
	t_list			*command;
	t_list			*redirect;
	struct s_cmd	*next;
} t_cmd;

#endif