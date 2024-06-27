/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:51:01 by yabejani          #+#    #+#             */
/*   Updated: 2024/03/07 13:48:53 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fd_print_s(int fd, const char *str)
{
	if (str == NULL)
		return (write(fd, "(null)", 6));
	else
		return (write(fd, str, ft_strlen(str)));
}
