#include "minishell.h"

int	tilde_expansor(t_scan *scan, t_shell *hell)
{
	char	*home;
	char	*tmp;
	int		home_len;

	home = get_value_env(hell->env, "HOME");
	if (!home)
	{
		scan->error = ft_strdup("HOME not set");
		scan->exit_code = 1;
		return (-42);
	}
	home_len = ft_strlen(home);
	tmp = ft_strrchr(scan->token, '~');
	if (!ft_strncmp(++tmp, "/", 1) || !ft_strncmp(tmp, "$", 1))
		swap(scan, ft_strjoin(home, tmp));
	else if (*tmp == '\0')
		swap(scan, ft_strdup(home));
	else
		home_len = 0;
	return (home_len);
}

int	var_expansor(t_scan *scan, t_shell *hell, int i)
{
	char	*new;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		j;

	j = 1;
	tmp = &scan->token[i];
	while ((ft_isalnum(tmp[j]) || tmp[j] == '_') && tmp[j])
		j++;
	new = ft_substr(tmp, 1, j - 1);
	tmp = tmp + j;
	tmp2 = get_value_env(hell->env, new);
	free(new);
	if (!tmp2)
		return ((j - 1) + i);
	if (tmp)
		tmp = ft_strjoin(tmp2, tmp);
	tmp3 = ft_substr(scan->token, 0, ft_strlen(scan->token)
			- ft_strlen(&scan->token[i]));
	swap(scan, ft_strjoin(tmp3, tmp));
	free(tmp3);
	if (tmp)
		free(tmp);
	return (ft_strlen(tmp2) + i);
}

int	token_expansor(t_scan *scan, t_shell *hell)
{
	int	i;
	int	is_simple_quoted;

	i = 0;
	is_simple_quoted = 0;
	if (scan->token[i] == '~')
	{
		i = tilde_expansor(scan, hell);
		if (i == -42)
			return (1);
	}
	while (scan->token[i])
	{
		if (scan->token[i] == '\'')
			is_simple_quoted = 1;
		if (scan->token[i] == '$' && !is_simple_quoted)
			i = var_expansor(scan, hell, i);
		i++;
	}
	check_var(scan, hell);
	remove_quote(scan);
	return (0);
}
