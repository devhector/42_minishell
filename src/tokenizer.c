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

static void	find_end_token(char *str, int *i, int isalnum)
{
	int	start;

	start = *i;
	if (isalnum)
	{
		while (str[*i] && !ft_isspace(str[*i]) && ft_isalnum(str[*i]))
			*i++;
		create_token(hell, start, *i);
	}
	else
	{
		while (str[*i] && !ft_isspace(str[*i]) && !ft_isalnum(str[*i]))
			*i++;
		create_token(hell, start, *i);
	}
}

static void	get_tokens(t_shell	*hell)
{
	int		i;
	int		start;
	char	*str;

	i = 0;
	str = hell->line;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			i++;
		else if (str[i] == '\'' || str[i] == '\"')
			create_quote_token(hell, &i);
		else if (!ft_isalnum(str[i]))
			find_end_token(str, &i, 0);
		else
			find_end_token(str, &i, 1);
	}
}

int	tokenizer(t_shell *hell)
{
	get_tokens(hell);
	return (0);
}
