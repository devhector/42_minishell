/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 12:16:23 by hectfern          #+#    #+#             */
/*   Updated: 2022/07/17 00:28:16 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list	**lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!*lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		del(tmp->content);
		tmp->content = NULL;
		tmp->prev = NULL;
		free(tmp);
		tmp = tmp2;
	}
	*lst = NULL;
}
