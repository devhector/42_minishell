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

static void	print_env(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(str[i], STDOUT_FILENO);
		i++;
	}
	free_array(str);
}

int	check_name(char	*str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	create_var(char *str, t_shell *hell)
{
	char		*key;
	char		*value;

	if (check_name(str))
	{
		key = get_key(str);
		value = get_value(str);
		update_env(hell->env, key, value);
		free(key);
	}
	else
	{
		ft_putstr_fd("minisHell: export: `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("': is not a valid identifier", STDERR_FILENO);
	}
}

void	export(t_cmd *cmd, t_shell *hell)
{
	int		i;
	char	*key;
	char	**args;

	i = 1;
	args = cmd->cmd_tab;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
			create_var(args[i], hell);
		else
		{
			if (check_name(args[i]))
			{
				key = ft_strdup(args[i]);
				update_env(hell->env, key, NULL);
				free(key);
			}
			else
			{
				ft_putstr_fd("minisHell: export: `", STDERR_FILENO);
				ft_putstr_fd(args[i], STDERR_FILENO);
				ft_putendl_fd("': is not a valid identifier", STDERR_FILENO);
			}
		}
		i++;
	}
}

int	b_export(t_cmd *cmd, t_shell *hell)
{
	char	**args;

	args = cmd->cmd_tab;
	if (count_args(args) == 1)
	{
		print_env(sort_array(hell->envp));
		return (0);
	}
	else
		export(cmd, hell);
	return (0);
}