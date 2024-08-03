/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:50:50 by mmakagon          #+#    #+#             */
/*   Updated: 2024/06/28 11:38:57 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pf_printint(const char *digits, int xx, int base, int sign)
{
	char				buf[16];
	unsigned int		x;
	int					i;
	int					len;

	if (sign)
		sign = xx < 0;
	if (sign)
		x = -xx;
	else
		x = xx;
	if (x == 0)
		return (write(STDOUT_FILENO, "0", 1));
	i = 0;
	while (x != 0)
	{
		buf[i++] = digits[x % base];
		x /= base;
	}
	if (sign)
		buf[i++] = '-';
	len = i;
	while (i-- > 0)
		write (STDOUT_FILENO, &(buf[i]), 1);
	return (len);
}

int	pf_printptr(const char *digits, uint64_t ptr)
{
	char	buf[20];
	int		i;
	int		len;

	if (ptr == 0)
		return (write(1, NLPTSTR, NLPTLEN));
	i = 0;
	while (ptr != 0)
	{
		buf[i++] = digits[ptr % 16];
		ptr /= 16;
	}
	len = i + 2;
	write (STDOUT_FILENO, "0x", 2);
	while (i-- > 0)
		write (STDOUT_FILENO, &(buf[i]), 1);
	return (len);
}

int	pf_printstr(char *str)
{
	int	len;

	if (!str)
		return (write(STDOUT_FILENO, "(null)", 6));
	len = 0;
	while (str[len])
		write(STDOUT_FILENO, &(str[len++]), 1);
	return (len);
}

int	pf_format(const char *fmt, va_list args)
{
	const char	digits[] = "0123456789abcdef";
	const char	cap_dgts[] = "0123456789ABCDEF";

	if (fmt && *fmt)
	{
		if (*fmt == 'd' || *fmt == 'i')
			return (pf_printint(digits, va_arg(args, int), 10, 1));
		else if (*fmt == 'u')
			return (pf_printint(digits, va_arg(args, int), 10, 0));
		else if (*fmt == 'x')
			return (pf_printint(digits, va_arg(args, int), 16, 0));
		else if (*fmt == 'X')
			return (pf_printint(cap_dgts, va_arg(args, int), 16, 0));
		else if (*fmt == 'c')
			return (ft_putchar_fd(va_arg(args, int), STDOUT_FILENO), 1);
		else if (*fmt == 'p')
			return (pf_printptr(digits, va_arg(args, uint64_t)));
		else if (*fmt == '%')
			return (write(STDOUT_FILENO, "%", 1));
		else if (*fmt == 's')
			return (pf_printstr(va_arg(args, char *)));
	}
	return (0);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	size_t	len;

	if (!fmt || !*fmt)
		return (0);
	va_start(args, fmt);
	len = 0;
	while (*fmt)
	{
		if (*fmt == '%')
			len += pf_format(++fmt, args);
		else
			len += write(STDOUT_FILENO, fmt, 1);
		fmt++;
	}
	va_end(args);
	return (len);
}
