#include "minishell.h"

void	assignment_word(t_shell *hell, char *str)
{
	if (!ft_strncmp(str, "$\0", 2))
		ft_lstadd_back(&hell->lexems, ft_lstnew(WORD));
	else
		ft_lstadd_back(&hell->lexems, ft_lstnew(ASSIGNMENT));
}

int	lexer(t_shell *hell)
{
	t_list	*tmp;
	char	*str;

	tmp = hell->tokens;
	while (tmp)
	{
		str = (char *)tmp->content;
		if (!ft_strncmp(str, "|", 1))
			ft_lstadd_back(&hell->lexems, ft_lstnew(PIPE));
		else if (!ft_strncmp(str, "<\0", 2))
			ft_lstadd_back(&hell->lexems, ft_lstnew(LESS));
		else if (!ft_strncmp(str, ">\0", 2) || !ft_strncmp(str, ">|", 2))
			ft_lstadd_back(&hell->lexems, ft_lstnew(GREAT));
		else if (!ft_strncmp(str, ">>", 2))
			ft_lstadd_back(&hell->lexems, ft_lstnew(DGREAT));
		else if (!ft_strncmp(str, "<<", 2))
			ft_lstadd_back(&hell->lexems, ft_lstnew(DLESS));
		else if (!ft_strncmp(str, "$", 1))
			assignment_word(hell, str);
		else
			ft_lstadd_back(&hell->lexems, ft_lstnew(WORD));
		tmp = tmp->next;
	}
}