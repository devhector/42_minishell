/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:38:49 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/24 12:50:19 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define WORD "WORD"
# define PIPE "PIPE"
# define LESS "LESS"
# define DLESS "DLESS"
# define GREAT "GREAT"
# define DGREAT "DGREAT"
# define ASSIGNMENT "ASSIGNMENT"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>
# include <wait.h>
# include <signal.h>
# include <errno.h>
# include "libft.h"
# include "hash_table.h"
# include "scan.h"
# include "command.h"

typedef struct s_shell
{
	int			exit_code;
	char		*line;
	t_list		*tokens;
	t_list		*cmd;
	t_hash_elem	**env;
	char		*error;
	char		**envp;
}	t_shell;

extern int		g_exit_code;

void		handle_signals(void);
void		handle_signals_child(void);
void		handle_signals_parent(void);
void		minishell(char	**envp);
void		get_tokens(t_shell *hell);
void		clean_shell(t_shell *hell);
void		print_error(t_shell *hell);
void		quote_token(t_shell *hell, int *i);
void		redirect_token(t_shell *hell, int *i);
void		create_token(t_shell *hell, int start, int i);
void		del_scan(void *content);
void		close_fd(t_cmd *cmd);
void		free_array(char **str);
void		del_scan(void *content);
void		free_cmd(void *content);
void		check_var(t_scan *s);
void		swap(t_scan *scan, char *token);
void		remove_quote(t_scan *scan);
void		exec_bultin(t_cmd *cmd, t_shell *hell);
void		errno_handle(char *str, int errnb);
void		wait_pids(pid_t *pid, int i);
void		close_fd_redirect(t_scan *redirect, t_cmd *cmd);
void		close_all_fd(t_shell *hell);

int			scan(t_shell *hell);
int			lexer(t_shell *hell);
int			syntax(t_shell *hell);
int			tokens_checker(t_shell *hell);
int			check_tokens(t_shell *hell);
int			is_redirect_str(char *type);
int			command(t_shell *hell);
int			expanse(t_shell *hell);
int			execute(t_shell *hell);
int			command_table(t_shell *hell);
int			open_pipes(t_shell *hell);
int			redirects(t_shell *hell);
int			here_doc(char *delimiter);
int			is_bultin(t_cmd *cmd);
int			update_env(t_hash_elem **env, char *key, char *value);
int			b_echo(t_cmd *cmd);
int			b_pwd(void);
int			b_cd(t_cmd *cmd, t_shell *hell);
int			b_env(t_cmd *cmd, t_shell *hell);
int			b_exit(t_cmd *cmd, t_shell *hell);
int			b_export(t_cmd *cmd, t_shell *hell);
int			b_unset(t_cmd *cmd, t_shell *hell);
int			hash(const char *key);
int			count_args(char **args);
int			token_expansor(t_scan *scan, t_shell *hell);
int			var_expansor(t_scan *scan, t_shell *hell, int i);
int			tilde_expansor(t_scan *scan, t_shell *hell);
int			check_quotes(t_scan *scan);
int			check_backslash_semicolon(t_scan *scan);
int			check_follow_pipe(t_list *token);
int			check_variable(t_list *token);
int			builtin_parent(t_cmd *cmd, t_shell *hell);
int			check_path(t_cmd *cmd, t_shell *hell);
int			space_in_cmd(char *str, t_shell *hell);

char		*get_value(char	*data);
char		*get_key(char	*data);
char		**hash_env(t_shell *hell);
char		*get_value_env(t_hash_elem **envp, char *str);
char		*path(t_shell *hell, t_cmd *cmd);
char		**copy_array(char **str);
char		**sort_array(char **str);

t_hash_elem	**create_table_env(char **envp);

#endif