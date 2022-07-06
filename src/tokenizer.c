#include "minishell.h"

static int	token_counter(char	*line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else
		{
			count++;
			while (line[i] && !ft_isspace(line[i]))
				i++;
		}
	}
	printf("token count: %d\n", count);
	return (count);
}

// static void	get_tokens(t_shell *hell)
// {
// 	int	i;
// 	int	j;
// 	int	start;

// 	i = 0;
// 	j = 0;
// 	while(hell->line[i])
// 	{
// 		if (ft_isspace(hell->line[i]))
// 			i++;
// 		else
// 		{
// 			start = i;
// 			while (hell->line[i] && !ft_isspace(hell->line[i]))
// 				i++;
// 			hell->tokens[j] = ft_substr(&hell->line[start], 0, i - start);
// 			j++;
// 		}
// 	}
// }

static void	get_tokens(t_shell *hell)
{
	int		i;
	int		start;
	char	*str;

	i = 0;
	while(hell->line[i])
	{
		if (ft_isspace(hell->line[i]))
			i++;
		else
		{
			start = i;
			while (hell->line[i] && !ft_isspace(hell->line[i]))
				i++;
			str = ft_substr(&hell->line[start], 0, i - start);
			ft_lstadd_back(&hell->tokens, ft_lstnew(str));
		}
	}
}

void delete_content(void *content)
{
	free((char *)content);
}

int	tokenizer (t_shell	*hell)
{

	hell->amt_tokens = token_counter(hell->line);
	printf("number of tokens: %d\n", hell->amt_tokens);
	get_tokens(hell);
	t_list *tmp = hell->tokens;
	while(tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&hell->tokens, delete_content);

	return (0);
}