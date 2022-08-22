/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:33:08 by hectfern          #+#    #+#             */
/*   Updated: 2022/08/20 14:33:10 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# include "libft.h"

# define HASH_SIZE 420

typedef struct s_hash_elem
{
	char				*key;
	char				*data;
	struct s_hash_elem	*next;
}	t_hash_elem;

void		clear_node(t_hash_elem *node);
void		init_table(t_hash_elem **table);
void		clear_table(t_hash_elem **table);
void		clear_element(t_hash_elem *elem);
void		insert_element(t_hash_elem **table, t_hash_elem *elem);

int			hash(const char *key);

t_hash_elem	*table_lookup(t_hash_elem **table, const char *key);
t_hash_elem	*remove_element(t_hash_elem **table, const char *key);

#endif