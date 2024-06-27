/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:08:42 by yabejani          #+#    #+#             */
/*   Updated: 2024/01/18 16:23:16 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(long int nbr)
{
	int	len;

	if (nbr <= 0)
		len = 1;
	else
		len = 0;
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static long long	ft_abs(long long n)
{
	long long	nb;

	if (n < 0)
		nb = -n;
	else
		nb = n;
	return (nb);
}

static char	*ft_mallocstr(size_t nbr)
{
	char	*str;

	str = malloc(sizeof(char) * (nbr + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_itoa(int nbr)
{
	int				len;
	int				sign;
	unsigned int	nb;
	char			*str;

	sign = 42;
	if (nbr < 0)
		sign = -1;
	len = ft_len(nbr);
	str = ft_mallocstr(len);
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	nb = ft_abs(nbr);
	while (len >= 0)
	{
		str[len] = nb % 10 + 48;
		nb = nb / 10;
		len--;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}

/*int	main(int argc, char **argv)
{
	(void)argc;
	printf("%s\n", ft_itoa(atoi(argv[1])));
}*/
