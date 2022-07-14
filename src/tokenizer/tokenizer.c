#include "minishell.h"

static void	create_token(t_shell *hell, int start, int i)
{
	char	*str;

	str = ft_substr(hell->line, start, i - start);
	ft_lstadd_back(&hell->tokens, ft_lstnew(str));
}

static void	create_quote_token(t_shell *hell, int *i)
{
	char	c;
	int		start;

	start = *i;
	*i += 1;
	c = hell->line[start];
	while (hell->line[*i] && hell->line[*i] != c)
		*i += 1;
	if (hell->line[*i])
		*i += 1;
	create_token(hell, start, *i);
}

static void	find_end_token(t_shell *hell, int *i, int isalnum)
{
	char	*str;
	int		start;

	start = *i;
	str = hell->line;
	if (isalnum)
	{
		while (str[*i] && !ft_isspace(str[*i]) && (ft_isalnum(str[*i])
				|| str[*i] == '_' || str[*i] == '-' || str[*i] == '='))
			*i += 1;
		create_token(hell, start, *i);
	}
	else
	{
		while (str[*i] && !ft_isspace(str[*i]) && !ft_isalnum(str[*i])
			&& str[*i] != '\"' && str[*i] != '\'' && str[*i] != '|')
			*i += 1;
		create_token(hell, start, *i);
	}
}

static void	get_tokens(t_shell	*hell)
{
	int		i;
	char	*str;

	i = 0;
	str = hell->line;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			i++;
		else if (str[i] == '|')
		{
			create_token(hell, i, i + 1);
			i++;
		}
		else if (str[i] == '\'' || str[i] == '\"')
			create_quote_token(hell, &i);
		else if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '-')
			find_end_token(hell, &i, 0);
		else
			find_end_token(hell, &i, 1);
	}
}

int	tokenizer(t_shell *hell)
{
	get_tokens(hell);
	t_list	*tmp;
	int		i = 0;
	tmp = hell->tokens;
	while (tmp)
	{
		printf("[%d] - %s\n", i, (char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
	printf("tokenks: %d\n", ft_lstsize(hell->tokens));
	printf("---------\n");
	if (tokens_checker(hell))
		printf("syntax error: quotes or redirections\n");
	tmp = hell->tokens;
	while (tmp)
	{
		printf("[%d] - %s\n", i, (char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
	ft_lstclear(&hell->tokens, free);
	return (0);
}
