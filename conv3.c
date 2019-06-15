/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conv3.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/13 20:19:13 by tide-jon       #+#    #+#                */
/*   Updated: 2019/06/15 15:44:20 by tide-jon      ########   odam.nl         */
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

