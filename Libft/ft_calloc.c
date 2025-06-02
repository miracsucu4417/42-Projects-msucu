/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:04:38 by msucu             #+#    #+#             */
/*   Updated: 2025/06/01 00:33:11 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*space;

	space = malloc(nmemb * size);
	if (space == NULL)
		return (NULL);
	ft_bzero(space, nmemb * size);
	return (space);
}
