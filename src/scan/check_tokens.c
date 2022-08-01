#include "minishell.h"

int	check_quotes(t_scan *scan)
{
	int		i;
	int		pos;
	char	*str;

	i = 0;
	str = scan->token;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			pos = i++;
			while (str[i] && str[i] != str[pos])
				i++;
			if (str[i] == '\0')
			{
				scan->error = ft_strdup("unclosed quote");
				return (1);
			}
			
		}
		i++;
	}
	return (0);
}

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
			scan->error = ft_strdup("syntax error");
			return (1);
		}
	}
	else if (str[0] == '<' && !(str[1] == '<' || str[1] == '\0'))
	{
		scan->error = ft_strdup("syntax error");
		return (1);
	}
	return (0);
}

int	check_backslash_semicolon(t_scan *scan)
{
	int		i;
	char	*str;

	i = 0;
	str = scan->token;
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == ';')
		{
			scan->error = ft_strdup("syntax error");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_follow_pipe(t_list *token)
{
	t_list	*next;
	t_scan	*scan;
	t_scan	*scan_next;

	if (token->next == NULL)
		return (0);
	next = token->next;
	scan = (t_scan *)token->content;
	scan_next = (t_scan *)next->content;
	if (scan->token[0] == '|' && scan_next->token[0] == '|')
	{
		scan->error = ft_strdup("syntax error");
		return (1);
	}
	return (0);
}

int	check_variable(t_list *token)
{
	int		i;
	t_scan	*scan;

	scan = (t_scan *)token->content;
	if (ft_strchr(scan->token, '='))
	{
		i = 0;
		if (ft_isdigit(scan->token[i]))
		{
			scan->error = ft_strdup("syntax error");
			return (1);
		}
		while (scan->token[i])
		{
			if (!ft_isalnum(scan->token[i]) && scan->token[i] != '_')
			{
				scan->error = ft_strdup("syntax error");
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int	check_tokens(t_shell *hell)
{
	t_list	*tmp;
	t_scan	*scan;

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
	return (0); //mudar isso para 0 por conta do if na linha 62 do scan.c
}