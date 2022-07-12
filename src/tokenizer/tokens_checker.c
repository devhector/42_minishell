int	check_quotes(t_shell *hell)
{
	t_list	*tmp;
	int		i;
	char	*str;
	char	c;

	i = 0;
	tmp = hell->tokens;
	while (tmp)
	{
		i = 0;
		str = (char *)tmp->content;
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
		tmp = tmp->next;
	}
	return (0);
}

int	tokens_checker(t_shell *hell)
{
	if (check_quotes(hell))
		return (1);
	return (0);
}