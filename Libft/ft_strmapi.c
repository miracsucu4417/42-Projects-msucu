/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:55:23 by msucu             #+#    #+#             */
/*   Updated: 2025/06/01 00:29:05 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

static char	*ft_create_empty_string(void)
{
	char	*empty_str;

	empty_str = (char *)ft_calloc(1, sizeof(char));
	if (empty_str == NULL)
		return (NULL);
	return (empty_str);
}

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*newstr;
	size_t			len;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	if (*s == '\0')
		return (ft_create_empty_string());
	len = ft_strlen(s);
	newstr = (char *) ft_calloc(len + 1, sizeof(char));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		newstr[i] = f(i, s[i]);
		i++;
	}
	return (newstr);
}
