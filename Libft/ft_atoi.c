/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:38:39 by msucu             #+#    #+#             */
/*   Updated: 2025/05/30 00:14:03 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

int	ft_atoi(char const *str)
{
	long long	num;
	int			sign;

	if (str == NULL || *str == '\0')
		return (0);
	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	num = 0;
	while (ft_isdigit(*str))
	{
		if (num > (LONG_MAX - (*str - '0')) / 10)
			return ((sign == 1) * -1 + (sign != 1) * 0);
		num = num * 10 + (*str - '0');
		str++;
	}
	return (sign * num);
}
