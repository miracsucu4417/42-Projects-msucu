/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:26:26 by msucu             #+#    #+#             */
/*   Updated: 2025/06/17 18:51:01 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digit_count(int n)
{
	int			digit_count;
	long int	long_n;

	long_n = (long int) n;
	digit_count = 0;
	if (long_n < 0)
	{
		long_n *= -1;
		digit_count++;
	}
	if (long_n == 0)
		digit_count = 1;
	while (long_n != 0)
	{
		long_n /= 10;
		digit_count++;
	}
	return (digit_count);
}

char	*ft_itoa(int n)
{
	int			digit_count;
	char		*str;
	int			i;
	long int	long_n;

	long_n = (long int) n;
	digit_count = ft_digit_count(n);
	str = (char *) ft_calloc(digit_count + 1, sizeof(char));
	if (str == FT_NULL)
		return (FT_NULL);
	if (long_n < 0)
	{
		long_n *= -1;
		str[0] = '-';
	}
	i = digit_count - 1;
	if (long_n == 0)
		str[0] = '0';
	while (i >= 0 && long_n != 0)
	{
		str[i] = (long_n % 10) + '0';
		long_n /= 10;
		i--;
	}
	return (str);
}
