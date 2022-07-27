#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_cmd
{
	t_list			*command;
	t_list			*redirect;
} t_cmd;

#endif