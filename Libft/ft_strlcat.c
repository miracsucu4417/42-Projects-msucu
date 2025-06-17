/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:03:43 by msucu             #+#    #+#             */
/*   Updated: 2025/06/17 18:57:28 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_size_t	ft_strlcat(char *dst, char const *src, t_size_t size)
{
	t_size_t	dest_len;
	t_size_t	src_len;
	t_size_t	i;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dest_len >= size)
		return (size + src_len);
	i = 0;
	while (i + dest_len + 1 < size && src[i] != '\0')
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}
