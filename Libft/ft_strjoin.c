/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:46:59 by msucu             #+#    #+#             */
/*   Updated: 2025/05/29 23:57:37 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*newstr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	newstr = ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (newstr == NULL)
		return (NULL);
	ft_memcpy(newstr, s1, s1_len);
	ft_memcpy(newstr + s1_len, s2, s2_len);
	return (newstr);
}
