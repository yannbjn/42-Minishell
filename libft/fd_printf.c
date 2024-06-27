/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:38:36 by yabejani          #+#    #+#             */
/*   Updated: 2024/03/07 13:49:51 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_type(int fd, char c, va_list args)
{
	if (c == 'c')
	{
		ft_putchar_fd(va_arg(args, int), fd);
		return (1);
	}
	else if (c == 's')
		return (fd_print_s(fd, va_arg(args, char *)));
	else if (c == 'p')
		return (fd_print_p(fd, va_arg(args, void *)));
	else if (c == 'd' || c == 'i')
		return (fd_print_di(fd, va_arg(args, int)));
	else if (c == 'u')
		return (fd_print_u(fd, va_arg(args, unsigned int)));
	else if (c == 'x')
		return (fd_print_xx(fd, va_arg(args, int), 1));
	else if (c == 'X')
		return (fd_print_xx(fd, va_arg(args, int), 42));
	else if (c == '%')
		return (write(fd, "%", 1));
	return (0);
}

int	fd_printf(int fd, const char *form, ...)
{
	int		len;
	int		i;
	va_list	args;

	if (!form)
		return (-1);
	len = 0;
	i = 0;
	va_start(args, form);
	while (form[i])
	{
		if (form[i] == '%')
		{
			i++;
			len += print_type(fd, form[i], args);
		}
		else
			len += write(fd, &form[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}
