/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 10:15:57 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/21 20:41:35 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	t_list	*prev;

	if (!lst)
		return ;
	prev = lst->prev;
	if (prev)
	{
		prev->next = lst->next;
		if (lst->next)
			lst->next->prev = prev;
		del(lst->content);
		free(lst);
		return ;
	}
	prev = lst->next;
	prev->prev = NULL;
	del(lst->content);
	free(lst);
	lst = prev;
}
