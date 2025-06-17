/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:19:51 by msucu             #+#    #+#             */
/*   Updated: 2025/06/17 20:30:54 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*previous_node;
	t_list	*next_node;

	if (lst == FT_NULL || *lst == FT_NULL || del == FT_NULL)
		return ;
	previous_node = *lst;
	next_node = (*lst)->next;
	while (next_node)
	{
		del(previous_node->content);
		free(previous_node);
		previous_node = next_node;
		next_node = next_node->next;
	}
	del(previous_node->content);
	free(previous_node);
	*lst = FT_NULL;
}
