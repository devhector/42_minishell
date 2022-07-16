/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_middle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 23:43:53 by hectfern          #+#    #+#             */
/*   Updated: 2022/07/17 00:25:08 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_middle(t_list	*elem, t_list	*new)
{
	t_list	*aux;

	if (!new)
		return ;
	aux = elem->next;
	aux->prev = new;
	elem->next = new;
	new->prev = elem;
	new->next = aux;
}
