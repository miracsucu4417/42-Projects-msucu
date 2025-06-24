/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:33:28 by msucu             #+#    #+#             */
/*   Updated: 2025/06/01 00:26:32 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static long int	ft_power(int base, int power)
{
	long int	result;

	result = 1;
	while (power > 0)
	{
		result *= base;
		power--;
	}
	return (result);
}

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

void	ft_putnbr_fd(int n, int fd)
{
	long int	power_of_ten;
	long int	long_n;
	char		c;

	power_of_ten = ft_power(10, ft_digit_count(n) - 1);
	long_n = (long int) n;
	if (long_n < 0)
	{
		write(fd, "-", 1);
		long_n *= -1;
		power_of_ten /= 10;
	}
	while (power_of_ten >= 1)
	{
		c = (long_n / power_of_ten) + '0';
		write(fd, &c, 1);
		long_n %= power_of_ten;
		power_of_ten /= 10;
	}
}
