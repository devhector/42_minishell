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
