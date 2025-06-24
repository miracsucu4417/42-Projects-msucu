/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:56:02 by msucu             #+#    #+#             */
/*   Updated: 2025/06/17 18:59:24 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, t_size_t n)
{
	unsigned char	*temp;
	unsigned char	temp_c;
	t_size_t		i;

	if (n == 0)
		return (FT_NULL);
	temp_c = (unsigned char) c;
	temp = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (temp[i] == temp_c)
			return ((void *) &(temp[i]));
		i++;
	}
	return (FT_NULL);
}
