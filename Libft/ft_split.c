/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:31:47 by msucu             #+#    #+#             */
/*   Updated: 2025/05/29 23:52:06 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_reset_arr(char **strarr, unsigned int i)
{
	while (i > 0)
		free(strarr[--i]);
	free(strarr);
	return (0);
}

static int	ft_add_word(char const *begin, char c, char **strarr, size_t i2)
{
	char const		*end;
	unsigned int	i;

	i = 0;
	while (begin[i])
	{
		if (begin[i] == c)
		{
			end = &begin[i - 1];
			strarr[i2] = ft_substr(begin, 0, end - begin + 1);
			if (strarr[i2] == NULL)
				return (ft_reset_arr(strarr, i2));
			return (1);
		}
		i++;
	}
	end = &begin[i - 1];
	strarr[i2] = ft_substr(begin, 0, end - begin + 1);
	if (strarr[i2] == NULL)
		return (ft_reset_arr(strarr, i2));
	return (1);
}

static int	ft_fill_arr(char const *s, char c, char **strarr)
{
	unsigned int	i;
	int				is_c;

	is_c = 1;
	i = 0;
	while (*s)
	{
		if (*s != c && is_c == 1)
		{
			is_c = 0;
			if (!ft_add_word(s, c, strarr, i))
				return (0);
			i++;
		}
		if (*s == c)
			is_c = 1;
		s++;
	}
	strarr[i] = NULL;
	return (1);
}

static size_t	ft_count_c(char const *s, char c)
{
	unsigned int	i;
	size_t			strarr_len;
	int				is_else;

	is_else = 0;
	strarr_len = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			is_else = 1;
		if (s[i] == c && is_else == 1)
		{
			strarr_len++;
			is_else = 0;
		}
		i++;
	}
	return (strarr_len);
}

char	**ft_split(char const *s, char c)
{
	char			**strarr;
	size_t			strarr_len;

	if (s == NULL)
		return (NULL);
	strarr_len = ft_count_c(s, c);
	strarr = (char **) ft_calloc(strarr_len + 1, sizeof(char *));
	if (strarr == NULL || ft_fill_arr(s, c, strarr) == 0)
		return (NULL);
	return (strarr);
}
