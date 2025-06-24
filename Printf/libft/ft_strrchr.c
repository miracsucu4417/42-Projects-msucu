/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:19:28 by msucu             #+#    #+#             */
/*   Updated: 2025/06/17 18:51:01 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *s, int c)
{
	char const	*end;

	end = s + ft_strlen(s);
	while (end != s && *end != (char) c)
		end--;
	if (*end == (char) c)
		return ((char *) end);
	else
		return (FT_NULL);
}
