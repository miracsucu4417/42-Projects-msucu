/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:55:23 by msucu             #+#    #+#             */
/*   Updated: 2025/06/17 18:58:40 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_create_empty_string(void)
{
	char	*empty_str;

	empty_str = (char *)ft_calloc(1, sizeof(char));
	if (empty_str == FT_NULL)
		return (FT_NULL);
	return (empty_str);
}

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*newstr;
	t_size_t		len;
	unsigned int	i;

	if (s == FT_NULL || f == FT_NULL)
		return (FT_NULL);
	if (*s == '\0')
		return (ft_create_empty_string());
	len = ft_strlen(s);
	newstr = (char *) ft_calloc(len + 1, sizeof(char));
	if (newstr == FT_NULL)
		return (FT_NULL);
	i = 0;
	while (s[i])
	{
		newstr[i] = f(i, s[i]);
		i++;
	}
	return (newstr);
}
