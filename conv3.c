/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conv3.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/13 20:19:13 by tide-jon       #+#    #+#                */
/*   Updated: 2019/06/17 17:56:46 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_putllnbr(long long n)
{
	long long	res;
	long long	m;

	m = n;
	if (m < 0)
	{
		m = m * -1;
		write(1, "-", 1);
	}
	res = m % 10 + '0';
	if ((m / 10) != 0)
		ft_putllnbr(m / 10);
	write(1, &res, 1);
}

char			*ft_strtoupper(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if ('a' <= str[i] && str[i] <= 'z')
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}
