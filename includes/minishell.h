#ifndef MINISHELL_H
# define MINISHELL_H

#define WORD "WORD"
#define PIPE "PIPE"
#define LESS "LESS"
#define DLESS "DLESS"
#define GREAT "GREAT"
#define DGREAT "DGREAT"
#define ASSIGNMENT "ASSIGNMENT"


#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "hash_table.h"
#include "scan.h"

typedef struct s_scan
{
	char	*token;
	char	*type;
} t_scan;

typedef struct s_shell
{
	int			amt_tokens;
	char		*line;
	t_list		*tokens;
	t_list		*lexems;
	t_hash_elem	**env;

} t_shell;

void		minishell(char	**envp);
void		get_tokens(t_shell *hell);

void	quote_token(t_shell *hell, int *i);
void	redirect_token(t_shell *hell, int *i);
void	create_token(t_shell *hell, int start, int i);

int			scan(t_shell *hell);
int			tokens_checker(t_shell *hell);
int	check_tokens(t_shell *hell);

t_hash_elem	**create_table_env(char **envp);


#endif