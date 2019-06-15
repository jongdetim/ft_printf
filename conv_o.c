/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conv_o.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/15 16:29:20 by tide-jon       #+#    #+#                */
/*   Updated: 2019/06/15 20:19:44 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned long long	typecast_o(t_printf *data, unsigned long long d)
{
	if (data->length == 'l')
		d = (unsigned long)d;
	if (data->length == '0')
		d = (unsigned int)d;
	if (data->length == 'c')
		d = (unsigned char)d;
	if (data->length == 'h')
		d = (unsigned short)d;
	return (d);
}

static	void				flaghandler2_o(t_printf *data, short extra,
													short len, short hash)
{
	short i;

	i = 0;
	while (i < extra - hash)
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
	if (hash == 1)
	{
		write(1, "0", 1);
		data->ret++;
	}
}

void						minus_o(int len, short extra, short hash,
														t_printf *data)
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

void						flaghandler_o(t_printf *data, int len, short hash,
														unsigned long long d)
{
	short		extra;
	short		i;

	i = 0;
	extra = 0;
	if (data->precision > len)
		extra = data->precision - len;
	while (data->width > i + len + extra + hash && data->minus == 0 &&
									(data->zero == 0 || data->dot == 1))
	{
		write(1, " ", 1);
		i++;
		data->ret++;
	}
	if (0 < extra - hash && data->minus == 0 &&
		data->precision < data->width && data->dot == 1)
	{
		write(1, " ", 1);
		data->ret++;
	}
	flaghandler2_o(data, extra, len, hash);
	if (data->precision == 0 && data->dot == 1 && d == 0)
	{
		if (data->width != 0)
			write(1, " ", 1);
		else
			data->ret--;
	}
	else
		ft_putstr(ft_itoabase(d, 8));
	data->ret += len;
	if (data->minus == 1)
		minus_o(len, extra, hash, data);
}

void						conv_o(t_printf *data)
{
	unsigned long long	d;
	int					len;
	short				i;
	short				hash;

	i = 0;
	hash = 0;
	d = va_arg(data->args, unsigned long long);
	d = typecast_o(data, d);
	if (data->hash == 1 && d != 0)
		hash = 1;
	len = ft_digcountbase(d, 8);
	flaghandler_o(data, len, hash, d);
}
