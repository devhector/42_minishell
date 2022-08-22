#include "minishell.h"

static int	check_redirections(t_scan *scan)
{
	char	*str;

	str = scan->token;
	if (str[0] == '>')
	{
		if (str[1] == '\0')
			return (0);
		else if (str[1] == '>' && !(str[2] == '\0' || str[2] == '|'))
		{
			scan->error = ft_strdup("syntax error redirect");
			scan->exit_code = 1;
			return (1);
		}
	}
	else if (str[0] == '<' && !(str[1] == '<' || str[1] == '\0'))
	{
		scan->error = ft_strdup("syntax error redirect");
		scan->exit_code = 1;
		return (1);
	}
	return (0);
}

void	print_tokens__(t_list *tokens)
{
	t_scan	*token;

	while (tokens)
	{
		token = tokens->content;
		printf("%s\n", token->token);
		tokens = tokens->next;
	}
}

int	check_tokens(t_shell *hell)
{
	t_list	*tmp;
	t_scan	*scan;

	print_tokens__(hell->tokens);
	tmp = hell->tokens;
	while (tmp)
	{
		scan = (t_scan *)tmp->content;
		if (check_quotes(scan))
			return ('q');
		if (check_redirections(scan))
			return ('r');
		if (check_backslash_semicolon(scan))
			return ('b');
		if (check_follow_pipe(tmp))
			return ('p');
		if (check_variable(tmp))
			return ('v');
		tmp = tmp->next;
	}
	return (0);
}
