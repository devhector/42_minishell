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
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <wait.h>
#include "libft.h"
#include "hash_table.h"
#include "scan.h"
#include "command.h"

typedef struct s_shell
{
	int			amt_tokens;
	char		*line;
	t_list		*tokens;
	t_list		*cmd;
	t_hash_elem	**env;
	char		*error;
	char		**envp;
} t_shell;

void		minishell(char	**envp);
void		get_tokens(t_shell *hell);

void	quote_token(t_shell *hell, int *i);
void	redirect_token(t_shell *hell, int *i);
void	create_token(t_shell *hell, int start, int i);

void del_scan(void *content);

int			scan(t_shell *hell);
int			lexer(t_shell *hell);
int			syntax(t_shell *hell);
int			tokens_checker(t_shell *hell);
int			check_tokens(t_shell *hell);
int			is_redirect_str(char *type);


char		**hash_env(t_shell *hell);
char		*get_value_env(t_hash_elem **envp, char *str);
t_hash_elem	**create_table_env(char **envp);

int	command(t_shell *hell);
int	expanse(t_shell *hell);
int	execute(t_shell *hell);
int	command_table(t_shell *hell);

int		open_pipes(t_shell *hell);
int		redirects(t_shell *hell);
void	close_fd(t_cmd *cmd);
void	open_file(t_list *redirect, t_cmd *cmd);
char	*path(t_shell *hell, t_cmd *cmd);

void	free_array(char **str);
void	del_scan(void *content);
void	free_cmd (void *content);

int		here_doc(char *delimiter);

#endif