/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:56:02 by msucu             #+#    #+#             */
/*   Updated: 2025/06/01 00:25:58 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	*ft_memchr(void const *s, int c, size_t n)
{
	unsigned char	*temp;
	unsigned char	temp_c;
	size_t			i;

	if (n == 0)
		return (NULL);
	temp_c = (unsigned char) c;
	temp = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (temp[i] == temp_c)
			return ((void *) &(temp[i]));
		i++;
	}
	return (NULL);
}
