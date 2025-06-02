/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:05:14 by msucu             #+#    #+#             */
/*   Updated: 2025/06/01 18:08:13 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(char const *big, char const *little, size_t len)
{
	size_t		i;
	size_t		j;

	if (*little == '\0')
		return ((char *)(big));
	if (len == 0)
		return (NULL);
	i = 0;
	while (i < len && big[i])
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (i + j < len && little[j] && big[i + j] == little[j])
				j++;
			if (little[j] == '\0')
				return ((char *) &big[i]);
		}
		i++;
	}
	return (NULL);
}
