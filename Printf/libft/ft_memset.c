/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:35:26 by msucu             #+#    #+#             */
/*   Updated: 2025/06/17 18:59:38 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, t_size_t n)
{
	unsigned char	*beginning;
	t_size_t		i;

	beginning = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		beginning[i] = (unsigned char) c;
		i++;
	}
	return (s);
}
