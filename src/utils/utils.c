#include "minishell.h"

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

char	**copy_array(char **str)
{
	int		i;
	int		size;
	char	**new;

	size = count_args(str);
	new = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (str[i])
	{
		new[i] = ft_strdup(str[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	**sort_array(char **str)
{
	int		i;
	int		j;
	char	*tmp;
	char	**new;

	i = 0;
	new = copy_array(str);
	while (new[i])
	{
		j = i + 1;
		while (new[j])
		{
			if (ft_strcmp(new[i], new[j]) > 0)
			{
				tmp = new[i];
				new[i] = new[j];
				new[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (new);
}
