#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "hash_table.h"

void		minishell(char	**envp);
t_hash_elem	**create_table_env(char **envp)


#endif