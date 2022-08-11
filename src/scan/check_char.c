int	is_redirect(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	is_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	has_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
			return (1);
		i++;
	}
	return (0);
}
