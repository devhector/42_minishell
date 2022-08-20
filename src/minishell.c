#include "minishell.h"

void init_shell(t_shell *hell, char **envp)
{
	hell->cmd = NULL;
	hell->envp = NULL;
	hell->line = NULL;
	hell->error = NULL;
	hell->tokens = NULL;
	hell->env = create_table_env(envp);
}

static void	reprompt(int signal)
{
	(void)signal;
	rl_replace_line("", 0);
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_signals(void)
{
	signal(SIGINT, reprompt);
	signal(SIGQUIT, SIG_IGN);
}

int	full_space(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*create_prompt(t_shell *hell)
{
	char	*usr;

	usr = ft_strdup(get_value_env(hell->env, "USER"));
	if (!usr)
		return (NULL);
	return (ft_strjoin(usr, " $> "));
}

void	minishell(char	**envp)
{
	t_shell	hell;

	init_shell(&hell, envp);
	while (42)
	{
		handle_signals();
		clean_shell(&hell);
		hell.line = readline("$> ");
		add_history(hell.line);
		if (!hell.line)
		{
			printf("exit\n"); //criar func exit
			break ;
		}
		if (!*hell.line || full_space(hell.line))
			continue ;
		if (scan(&hell) || execute(&hell))
		{
			print_error(&hell);
			continue;
		}
	}
	clear_table(hell.env);
	rl_clear_history();
}