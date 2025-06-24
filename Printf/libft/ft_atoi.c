/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:38:39 by msucu             #+#    #+#             */
/*   Updated: 2025/06/17 18:57:51 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

int	ft_atoi(char const *nptr)
{
	long long	num;
	int			sign;

	if (*nptr == '\0')
		return (0);
	while (ft_isspace(*nptr))
		nptr++;
	sign = 1;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	num = 0;
	while (ft_isdigit(*nptr))
	{
		if (num > (FT_LONG_MAX - (*nptr - '0')) / 10)
			return ((sign == 1) * -1 + (sign != 1) * 0);
		num = num * 10 + (*nptr - '0');
		nptr++;
	}
	return ((int)(sign * num));
}
