#include "minishell.h"

void	swap(t_scan *scan, char *token)
{
	free(scan->token);
	scan->token = token;
}

void	check_var(t_scan *scan, t_shell *hell)
{
	int	i;

	i = 0;
	if (scan->token[i] == '$')
	{
		i++;
		while ((ft_isalnum(scan->token[i]) || scan->token[i] == '_')
			&& scan->token[i])
			i++;
	}
	i = 0;
	if (scan->token[i] == '$' && scan->token[i + 1] == '\0')
	{
		free(scan->token);
		scan->token = ft_strdup("");
	}
	if (scan->token[0] == '$' && scan->token[1] == '?'
		&& scan->token[2] == '\0')
	{
		free(scan->token);
		scan->token = ft_itoa(hell->exit_code);
	}
}

void	remove_quote(t_scan *scan)
{
	char	*tmp;

	if (has_quote(scan->token))
	{
		tmp = ft_substr(scan->token, 1, ft_strlen(scan->token) - 2);
		free(scan->token);
		scan->token = tmp;
	}
}

int	expanse(t_shell *hell)
{
	t_list	*tmp;
	t_list	*cmd;

	cmd = hell->cmd;
	while (cmd)
	{
		tmp = ((t_cmd *)cmd->content)->command;
		while (tmp)
		{
			if (token_expansor(tmp->content, hell))
				return (1);
			tmp = tmp->next;
		}
		tmp = ((t_cmd *)cmd->content)->redirect;
		while (tmp)
		{
			if (token_expansor(tmp->content, hell))
				return (1);
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
	return (command_table(hell));
}
