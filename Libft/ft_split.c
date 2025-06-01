/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:31:47 by msucu             #+#    #+#             */
/*   Updated: 2025/06/01 18:52:48 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_reset_arr(char **strarr, unsigned int i)
{
	while (i > 0)
		free(strarr[--i]);
	free(strarr);
	return (0);
}

static int	ft_add_word(char const *begin, char c, char **strarr, size_t i2)
{
	size_t	len;

	len = 0;
	while (begin[len] && begin[len] != c)
		len++;
	strarr[i2] = ft_substr(begin, 0, len);
	if (strarr[i2] == NULL)
		return (ft_reset_arr(strarr, i2));
	return (1);
}

static int	ft_fill_arr(char const *s, char c, char **strarr)
{
	unsigned int	i;
	int				in_word;

	in_word = 0;
	i = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			if (!ft_add_word(s, c, strarr, i))
				return (0);
			i++;
		}
		if (*s == c)
			in_word = 0;
		s++;
	}
	strarr[i] = NULL;
	return (1);
}

static size_t	ft_count_words(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char			**strarr;
	size_t			strarr_len;

	if (s == NULL)
	{
		strarr = (char **) ft_calloc(1, sizeof(char *));
		strarr[0] = NULL;
		return (strarr);
	}
	strarr_len = ft_count_words(s, c);
	strarr = (char **) ft_calloc(strarr_len + 1, sizeof(char *));
	if (strarr == NULL)
		return (NULL);
	if (ft_fill_arr(s, c, strarr) == 0)
		return (NULL);
	return (strarr);
}
