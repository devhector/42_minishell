#include "minishell.h"

char	**create_cmd_tab(t_list *token)
{
	char	**cmd_tab;
	int		i;
	t_scan	*s;

	i = 0;
	cmd_tab = (char **)malloc(sizeof(char *) * (ft_lstsize(token) + 1));
	if (!cmd_tab)
		return (NULL);
	while (token)
	{
		s = (t_scan *)token->content;
		cmd_tab[i] = ft_strdup(s->token);
		token = token->next;
		i++;
	}
	cmd_tab[i] = NULL;
	return (cmd_tab);
}

int	command_table(t_shell *hell)
{
	t_list	*cmd;
	t_list	*token;
	t_cmd	*cmd_tmp;

	cmd = hell->cmd;
	while (cmd)
	{
		cmd_tmp = (t_cmd *)cmd->content;
		token = cmd_tmp->command;
		cmd_tmp->cmd_tab = create_cmd_tab(token);
		if (!cmd_tmp->cmd_tab)
		{
			((t_scan *)cmd->content)->error = ft_strdup(": malloc error");
			return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}
