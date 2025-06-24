/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:15:27 by msucu             #+#    #+#             */
/*   Updated: 2025/06/17 18:59:52 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char const *s)
{
	t_size_t	len;
	char		*new_str;

	len = ft_strlen(s);
	new_str = (char *) ft_calloc(len + 1, sizeof(char));
	if (new_str == FT_NULL)
		return (FT_NULL);
	ft_memcpy(new_str, s, len);
	return (new_str);
}
