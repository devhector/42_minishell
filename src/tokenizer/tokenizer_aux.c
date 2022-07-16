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

static void	create_dollar_token(t_shell *hell, int *i)
{
	int		start;

<<<<<<< HEAD
	if (hell->line[*i + 1] != ' ')
=======
	if (hell->line[*i + 1] == ' ')
>>>>>>> lexical_analytics
	{
		create_token(hell, *i, *i + 1);
		*i += 1;
	}
	else
	{
		start = *i;
		*i += 1;
<<<<<<< HEAD
		while(hell->line[*i] && !ft_isspace(hell->line[*i])
			&& hell->line[*i] != '$' && hell->line[*i] != '>'
			&& hell->line[*i] != '<')
=======
		while (hell->line[*i] && !ft_isspace(hell->line[*i])
			&& hell->line[*i] != '$' && hell->line[*i] != '>'
			&& hell->line[*i] != '<' && hell->line[*i] != '|')
>>>>>>> lexical_analytics
			*i += 1;
		create_token(hell, start, *i);
	}
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

void	get_tokens(t_shell	*hell)
{
	int		i;
	char	*str;

	i = 0;
	str = hell->line;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			i++;
		else if (str[i] == '$')
			create_dollar_token(hell, &i);
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
