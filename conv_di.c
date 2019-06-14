/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conv2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/13 20:19:14 by tide-jon       #+#    #+#                */
/*   Updated: 2019/06/13 20:19:17 by tide-jon      ########   odam.nl         */
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

/*
**	somehow also works for the the lowest possible value of each length type...
*/

static	void	flaghandler2_d(t_printf *data, short extra, short len, short min)
{
	short	i;

	i = 0;
	if (data->space == 1 && data->plus == 0 && min == 0)
		write(1, " ", 1);
	if (min == 1)
		write(1, "-", 1);
	while (i < extra)
	{
		write(1, "0", 1);
		i++;
	}
	i = 0;
	while (data->width > i + len + extra + min && data->zero == 1 &&
									data->minus == 0 && data->dot == 0)
	{
		write(1, "0", 1);
		i++;
	}
}

static	short	flaghandler_d(t_printf *data, long long d, short min)
{
	int			len;
	short		extra;
	short		i;

	i = 0;
	extra = 0;
	len = ft_digcountbase(d, 10);
	if (data->precision > len)
		extra = data->precision - len;
	while (data->width > i + len + extra + min && data->minus == 0 &&
									(data->zero == 0 || data->dot == 1))
	{
		write(1, " ", 1);
		i++;
	}
	i = 0;
	if (data->plus == 1 && min == 0)
		write(1, "+", 1);
	flaghandler2_d(data, extra, len, min);
	return (len);
}

void			conv_d(t_printf *data)
{
	long long	d;
	short		min;
	int			len;
	short		i;

	min = 0;
	i = 0;
	d = va_arg(data->args, long long);
	d = typecast(data, d);
	if (d < 0)
	{
		min = 1;
		d *= -1;
	}
	len = flaghandler_d(data, d, min);
	ft_putllnbr(d);
	while (data->width > i + len + min && data->minus == 1)
	{
		write(1, " ", 1);
		i++;
	}
}
