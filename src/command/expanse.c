#include "minishell.h"

void	swap(t_scan *scan, char *token)
{
	free(scan->token);
	scan->token = token;
}

int	tilde_expansor(t_scan *scan, t_shell *hell)
{
	char	*home;
	char	*tmp;
	int		home_len;

	home = get_value_env(hell->env, "HOME");
	if (!home)
	{
		scan->error = ft_strdup("HOME not set");
		return (-42);
	}
	home_len = ft_strlen(home);
	tmp = ft_strrchr(scan->token, '~');
	if (!ft_strncmp(++tmp, "/", 1) || !ft_strncmp(tmp, "$", 1))
		swap(scan, ft_strjoin(home, tmp));
	else if (*tmp == '\0')
		swap(scan, ft_strdup(home));
	else 
		home_len = 1;
	return (home_len);
}

int	var_expansor(t_scan *scan, t_shell *hell, int i)
{
	char	*new;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		len;

	len = 1;
	tmp = &scan->token[i];
	while ((ft_isalnum(tmp[len]) || tmp[len] == '_') && tmp[len])
		len++;
	new = ft_substr(tmp, 1, len - 1);
	tmp = tmp + len;
	tmp2 = get_value_env(hell->env, new);
	free(new);
	if (!tmp2)
		return ((len - 1) + i);
	if (tmp)
		tmp = ft_strjoin(tmp2, tmp);
	tmp3 = ft_substr(scan->token, 0, ft_strlen(scan->token) - ft_strlen(&scan->token[i]));
	swap(scan, ft_strjoin(tmp3, tmp));
	free(tmp3);
	if (tmp)
		free(tmp);
	return (ft_strlen(tmp2) + i);
}

int	token_expansor(t_scan *scan, t_shell *hell)
{
	int	i;

	i = 0;
	if (scan->token[i] == '~')
	{
		i = tilde_expansor(scan, hell);
		if (i == -42)
			return (1);
	}
	while (scan->token[i])
	{
		if (scan->token[i] == '$')
			i = var_expansor(scan, hell, i);
		i++;
	}
	return (0);
}

int	expanse(t_shell *hell)
{
	t_list	*tmp;
	t_scan	*s;

	tmp = ((t_cmd *)hell->cmd->content)->command;
	while (tmp)
	{
		s = (t_scan *)tmp->content;
		if (token_expansor(s, hell))
			return (1);
		tmp = tmp->next;
	}
	tmp = ((t_cmd *)hell->cmd->content)->redirect;
	while (tmp)
	{
		s = (t_scan *)tmp->content;
		if (token_expansor(s, hell))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}