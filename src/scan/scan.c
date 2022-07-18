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
	ft_lstclear(&hell->tokens, del);
}

int	scan(t_shell *hell)
{
	int		i;
	int		start;
	char	*line;

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
	print_tokens(hell);
	return (0);
}