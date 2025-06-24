/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:00:34 by msucu             #+#    #+#             */
/*   Updated: 2025/06/17 18:51:01 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char const *s, int c)
{
	char	letter;

	letter = (char) c;
	while (*s && *s != letter)
		s++;
	if (*s == letter)
		return ((char *) s);
	else
		return (FT_NULL);
}
