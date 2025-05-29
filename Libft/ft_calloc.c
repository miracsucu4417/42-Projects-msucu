/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:04:38 by msucu             #+#    #+#             */
/*   Updated: 2025/05/29 23:48:45 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_calloc_empty(void)
{
	void	*empty;

	empty = malloc(1);
	if (empty == NULL)
		return (NULL);
	return (empty);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*space;

	if (nmemb == 0 || size == 0)
		return (ft_calloc_empty());
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	space = malloc(nmemb * size);
	if (space == NULL)
		return (NULL);
	ft_bzero(space, nmemb * size);
	return (space);
}
