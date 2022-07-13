#include "minishell.h"

static int	check_quotes(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (!str[i])
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
		else if (str[1] == '>' && str[2] != '\0')
			return (1);
	}
	else if (str[0] == '<' && !(str[1] == '<' || str[1] == '\0'))
		return (1);
	return (0);
}

int	tokens_checker(t_shell *hell)
{
	char	*str;
	t_list	*tmp;

	tmp = hell->tokens;
	while (tmp)
	{
		str = (char *)tmp->content;
		if (check_quotes(str))
			return (1);
		if (check_redirections(str))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
