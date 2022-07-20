#include "minishell.h"

void	assignment_word(t_scan *scan, char *str)
{
	if (!ft_strncmp(str, "$\0", 2))
		scan->type = ft_strdup(WORD);
	else
		scan->type = ft_strdup(ASSIGNMENT);
}

void	word(t_scan *scan)
{
	int		i;
	char	*str;

	i = 0;
	str = scan->token;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			i++;
			while (str[i] && !is_quote(str[i]))
				i++;
		}
		if (str[i] == '=')
		{
			scan->type = ft_strdup(ASSIGNMENT);
			return ;
		}
		i++;
	}
	scan->type = ft_strdup(WORD);
}

int	lexer(t_shell *hell)
{
	t_list	*tmp;
	char	*str;
	t_scan	*scan;

	tmp = hell->tokens;
	while (tmp)
	{
		scan = (t_scan *)tmp->content;
		str = scan->token;
		if (!ft_strncmp(str, "|", 1))
			scan->type = ft_strdup(PIPE);
		else if (!ft_strncmp(str, "<\0", 2))
			scan->type = ft_strdup(LESS);
		else if (!ft_strncmp(str, ">\0", 2) || !ft_strncmp(str, ">|", 2))
			scan->type = ft_strdup(GREAT);
		else if (!ft_strncmp(str, ">>", 2))
			scan->type = ft_strdup(DGREAT);
		else if (!ft_strncmp(str, "<<", 2))
			scan->type = ft_strdup(DLESS);
		else if (!ft_strncmp(str, "$", 1))
			assignment_word(scan, str);
		else
			word(scan);
		tmp = tmp->next;
	}
	return (0);
}