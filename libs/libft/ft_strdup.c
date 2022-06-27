/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:02:13 by hectfern          #+#    #+#             */
/*   Updated: 2022/01/07 19:16:31 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t		size;
	size_t		i;
	char		*cp_str;

	i = 0;
	while (s[i])
		i++;
	size = (i + 1);
	cp_str = (char *)malloc(size * sizeof(char));
	if (!cp_str)
		return (NULL);
	i = 0;
	while (i < size)
	{
		cp_str[i] = s[i];
		i++;
	}
	return (cp_str);
}
