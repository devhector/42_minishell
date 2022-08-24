/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:36:01 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/24 07:00:28 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

int	main(int argc, char **argv, char **envp)
{
	if (argc > 1 || argv[1])
	{
		printf("error: invalid argument\n");
		return (1);
	}
	g_exit_code = 0;
	minishell(envp);
	return (g_exit_code);
}
