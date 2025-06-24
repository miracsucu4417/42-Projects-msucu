/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:46:59 by msucu             #+#    #+#             */
/*   Updated: 2025/06/17 19:01:30 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	t_size_t	s1_len;
	t_size_t	s2_len;
	char		*newstr;

	if (s1 == FT_NULL || s2 == FT_NULL)
		return (FT_NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	newstr = ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (newstr == FT_NULL)
		return (FT_NULL);
	ft_memcpy(newstr, s1, s1_len);
	ft_memcpy(newstr + s1_len, s2, s2_len);
	return (newstr);
}
