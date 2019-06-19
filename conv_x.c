/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conv_x.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/17 16:39:03 by tide-jon       #+#    #+#                */
/*   Updated: 2019/06/17 17:56:03 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	flaghandler_x_zero(t_printf *data, short extra,
										short len, short hash)
{
	short i;

	i = 0;
	if (hash == 2)
	{
		if (data->type == 'x')
			write(1, "0x", 2);
		else
			write(1, "0X", 2);
		data->ret += 2;
	}
	while (i < extra)
	{
		write(1, "0", 1);
		i++;
		data->ret++;
	}
	i = 0;
	while (data->width > i + len + extra - hash && data->zero == 1 &&
									data->minus == 0 && data->dot == 0)
	{
		write(1, "0", 1);
		i++;
		data->ret++;
	}
}

void			minus_x(int len, short extra, short hash, t_printf *data)
{
	int i;

	i = 0;
	while (data->width > i + len + extra + hash)
	{
		write(1, " ", 1);
		i++;
		data->ret++;
	}
	if (0 < extra - hash && data->precision < data->width &&
										data->dot == 1)
	{
		write(1, " ", 1);
		data->ret++;
	}
}

void			flaghandler_x_space(t_printf *data, int len,
							short hash, short extra)
{
	int	i;

	i = 0;
	while (data->width > i + len + extra + hash && data->minus == 0 &&
									(data->zero == 0 || data->dot == 1))
	{
		write(1, " ", 1);
		i++;
		data->ret++;
	}
	if (0 < extra - hash && data->minus == 0 && data->precision > len &&
						data->precision < data->width && data->dot == 1)
	{
		write(1, " ", 1);
		data->ret++;
	}
}

void			flaghandler_x(t_printf *data, int len, short hash,
														unsigned long long d)
{
	short		extra;

	extra = 0;
	if (data->precision > len)
		extra = data->precision - len;
	flaghandler_x_space(data, len, hash, extra);
	flaghandler_x_zero(data, extra, len, hash);
	if (data->precision == 0 && data->dot == 1 && d == 0)
	{
		if (data->width != 0)
			write(1, " ", 1);
		else
			data->ret--;
	}
	else if (data->type == 'x')
		ft_putstr(ft_itoabase(d, 16));
	else
		ft_putstr(ft_strtoupper(ft_itoabase(d, 16)));
	data->ret += len;
	if (data->minus == 1)
		minus_x(len, extra, hash, data);
}

void			conv_x(t_printf *data)
{
	unsigned long long	d;
	int					len;
	short				hash;

	hash = 0;
	d = va_arg(data->args, unsigned long long);
	d = typecast_u(data, d);
	if (data->hash == 1 && d != 0)
		hash = 2;
	len = ft_digcountbase(d, 16);
	flaghandler_x(data, len, hash, d);
}
