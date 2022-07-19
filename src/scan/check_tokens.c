#include "minishell.h"

int	check_quotes(char *str)
{
	int	i;
	int	pos;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			pos = i++;
			while (str[i] && str[i] != str[pos])
				i++;
			if (str[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

static int	check_redirections(char *str)
{
	if (str[0] == '>')
	{
		if (str[1] == '\0')
			return (0);
		else if (str[1] == '>' && !(str[2] == '\0' || str[2] == '|'))
			return (1);
	}
	else if (str[0] == '<' && !(str[1] == '<' || str[1] == '\0'))
		return (1);
	return (0);
}

int	check_backslash_semicolon(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == ';')
			return (1);
		i++;
	}
	return (0);
}

int	check_tokens(t_shell *hell)
{
	char	*str;
	t_list	*tmp;
	t_scan	*scan;

	tmp = hell->tokens;

	while (tmp)
	{
		scan = (t_scan *)tmp->content;
		str = scan->token;
		if (check_quotes(str))
			return ('q');
		if (check_redirections(str))
			return ('r');
		if (check_backslash_semicolon(str))
			return ('b');
		tmp = tmp->next;
	}
	return (0);
}