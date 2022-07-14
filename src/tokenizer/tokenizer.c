#include "minishell.h"

int	tokenizer(t_shell *hell)
{
	get_tokens(hell);
	t_list	*tmp;
	int		i = 0;
	tmp = hell->tokens;
	while (tmp)
	{
		printf("[%d] - %s\n", i, (char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
	printf("tokenks: %d\n", ft_lstsize(hell->tokens));
	printf("---------\n");
	if (tokens_checker(hell))
		printf("syntax error: quotes or redirections\n");
	tmp = hell->tokens;
	while (tmp)
	{
		printf("[%d] - %s\n", i, (char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
	ft_lstclear(&hell->tokens, free);
	return (0);
}
