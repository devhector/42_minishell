#include "minishell.h"

void del_scan(void *content)
{
	t_scan *scan;

	scan = (t_scan *)content;
	if (scan->token)
	{
		free(scan->token);
		scan->token = NULL;
	}
	if (scan->type)
	{
		free(scan->type);
		scan->type = NULL;
	}
	if (scan->error)
	{
		free(scan->error);
		scan->error = NULL;
	}
	free(scan);
	scan = NULL;
}

void free_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void free_cmd (void *content)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	if (cmd->cmd_tab)
	{
		free_array(cmd->cmd_tab);
		cmd->cmd_tab = NULL;
	}
	tmp = cmd->command;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	tmp = cmd->redirect;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	free(cmd);
	cmd = NULL;
}

void	print_tokens (t_shell *hell)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = hell->tokens;
	while (tmp)
	{
		printf("[%d] - %s\n", i, ((t_scan *)tmp->content)->token);
		tmp = tmp->next;
		i++;
	}
	printf("tokenks: %d\n", ft_lstsize(hell->tokens));
	printf("---------\n");
}

void print_scan(t_list *tokens)
{
	t_list	*tmp;
	t_scan	*scan;

	tmp = tokens;
	while (tmp)
	{
		scan = (t_scan *)tmp->content;
		if (scan->token)
			printf("%s - %s\n", scan->token, scan->type);
		tmp = tmp->next;
	}
}

int	scan(t_shell *hell)
{
	int		i;
	int		start;
	char	*line;
	int		error;

	i = 0;
	hell->cmd = NULL;
	line = hell->line;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (is_quote(line[i]))
			quote_token(hell, &i);
		else if (is_redirect(line[i]))
			redirect_token(hell, &i);
		else
		{
			start = i;
			while (line[i] && !ft_isspace(line[i]) && !is_redirect(line[i]))
				i++;
			create_token(hell, start, i);
		}
	}
	error = check_tokens(hell);
	if (error)
	{
		ft_lstclear(&hell->tokens, del_scan);
		return (error);
	}

	print_tokens(hell);

	if (lexer(hell))
	{
		printf("lexer error\n");
		return (1);
	}
	if (syntax(hell))
	{
		printf("syntax error\n");
		return (1);
	}
	if (command(hell))
	{
		printf("command error\n");
		return (1);
	}
	return (0);
}