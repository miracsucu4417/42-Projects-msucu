/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msucu <msucu@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:04:43 by msucu             #+#    #+#             */
/*   Updated: 2025/06/24 17:40:11 by msucu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

static int	ft_find_type(char c)
{
	/* Türler:
	0: char
	1: string
	2: pointer
	3: d
	*/
	if (c == 'c')
		return (0);
}
(c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
	|| c == 'u' || c == 'x' || c == 'X' || c == '%')
int ft_printf(const char *format, ...)
{
	va_list args;
	int		temp;
	char	c;

	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			c = *(format + 1);
			if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
				|| c == 'u' || c == 'x' || c == 'X' || c == '%')
				temp = va_arg(args, int);
			else
				write(1, format, 1);
		}
		else
			write(1, format, 1);
		format++;
	}
	va_end(args);
}
