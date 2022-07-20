#include "minishell.h"

void del(void *content)
{
	t_scan *scan;

	scan = (t_scan *)content;
	if (scan->token)
		free(scan->token);
	if (scan->type)
		free(scan->type);
	free(scan);
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
	printf("check_tokens: %d : %c\n", check_tokens(hell), (char)check_tokens(hell));
	error = check_tokens(hell);

	print_tokens(hell);
	lexer(hell);
	print_scan(hell->tokens);

	if (error) //esse if
	{
		ft_lstclear(&hell->tokens, del);
		return (error);
	}

	return (0);
}