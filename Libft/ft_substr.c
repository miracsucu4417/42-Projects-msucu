/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:09:09 by msucu             #+#    #+#             */
/*   Updated: 2025/06/17 18:57:28 by msucu            ###   ########.fr       */
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

char	*ft_substr(char const *s, unsigned int start, t_size_t len)
{
	unsigned int	s_len;
	unsigned int	substr_len;
	char			*substr;

	if (s == FT_NULL)
		return (FT_NULL);
	s_len = (unsigned int) ft_strlen(s);
	if (start > s_len || len == 0)
		return (ft_create_empty_string());
	substr_len = (unsigned int) len;
	if (s_len - start < len)
		substr_len = s_len - start;
	substr = (char *) ft_calloc(substr_len + 1, sizeof(char));
	if (substr == FT_NULL)
		return (FT_NULL);
	s += start;
	ft_memmove(substr, s, substr_len);
	return (substr);
}
