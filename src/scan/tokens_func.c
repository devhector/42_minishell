#include "minishell.h"

void	create_token(t_shell *hell, int start, int i)
{
	t_scan	*scan;

	scan = malloc(sizeof(t_scan));
	scan->token = ft_substr(hell->line, start, i - start);
	scan->type = NULL;
	ft_lstadd_back(&hell->tokens, ft_lstnew(scan));
}

void	redirect_token(t_shell *hell, int *i)
{
	int	start;

	start = *i;
	if (hell->line[*i] == '|')
	{
		create_token(hell, *i, *i + 1);
		*i += 1;
	}
	else
	{
		while (is_redirect(hell->line[*i]))
			*i += 1;
		create_token(hell, start, *i);
	}
}

void	quote_token(t_shell *hell, int *i)
{
	int		start;
	char	*line;

	start = *i;
	*i += 1;
	line = hell->line;
	while (line[*i] && line[*i] != hell->line[start])
		*i += 1;
	if (line[*i] == hell->line[start])
	{
		*i += 1;
		create_token(hell, start, *i);
	}
	else
		create_token(hell, start, *i);
}
