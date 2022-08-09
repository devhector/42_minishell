#ifndef BUILTIN_H
#define BUILTIN_H

#include minishell.h

int	echo(char *args, int fd)
int	env(t_hash_elem **table, int fd)
int export(char *args, t_hash_elem **table)
