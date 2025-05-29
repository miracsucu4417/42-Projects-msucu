/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:53:46 by msucu             #+#    #+#             */
/*   Updated: 2025/05/29 21:49:17 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*begin;
	char const	*end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	begin = s1;
	while (ft_strchr(set, *begin))
		begin++;
	end = s1 + ft_strlen(s1) - 1;
	while (ft_strchr(set, *end))
		end--;
	return (ft_substr(s1, begin - s1, end - begin + 1));
}
