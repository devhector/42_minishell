/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 14:06:42 by hectfern          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/27 01:26:41 by hectfern         ###   ########.fr       */
=======
/*   Updated: 2022/08/04 11:39:16 by hectfern         ###   ########.fr       */
>>>>>>> 0611a22 (fix: bug fix)
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char	*s1, char const	*s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
		s1 = ft_strdup("");
	if (!s1 || !s2)
		return (NULL);
	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
		j++;
	str = ft_calloc(i + j + 4, sizeof(char));
	if (!str)
		return (NULL);
	j = 0;
	ft_strlcpy(str, s1, i + 1);
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
