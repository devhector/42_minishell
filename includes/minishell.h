#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "hash_table.h"

typedef struct s_shell
{
	int			amt_tokens;
	char		*line;
	t_list		*tokens;
	t_hash_elem	**env;

} t_shell;

void		minishell(char	**envp);
int			tokenizer (t_shell	*hell);
int			tokens_checker(t_shell *hell);
t_hash_elem	**create_table_env(char **envp);


#endif