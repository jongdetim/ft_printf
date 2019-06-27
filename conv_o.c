/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conv_o.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/15 16:29:20 by tide-jon       #+#    #+#                */
/*   Updated: 2019/06/27 20:29:03 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	flaghandler_o_zero(t_printf *data, short extra,
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

static void		minus_o(int len, short extra, short hash, t_printf *data)
{
	int i;

	i = 0;
	while (data->width > i + len + extra + hash)
	{
		write(1, " ", 1);
		i++;
		data->ret++;
	}
}

static void		flaghandler_o_space(t_printf *data, int len,
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
}

static void		put_o(unsigned long long d)
{
	char	*temp;

	temp = ft_itoabase(d, 8);
	ft_putstr(temp);
	free(temp);
}

static void		flaghandler_o(t_printf *data, int len, short hash,
												unsigned long long d)
{
	short		extra;

	extra = 0;
	if (data->precision > len)
		extra = data->precision - len;
	flaghandler_o_space(data, len, hash, extra);
	flaghandler_o_zero(data, extra, len, hash);
	if (data->precision == 0 && data->dot == 1 && d == 0)
	{
		if (data->width != 0 && data->hash == 0)
			write(1, " ", 1);
		else if (data->hash == 0)
			data->ret--;
		else
			write(1, "0", 1);
	}
	else
		put_o(d);
	data->ret += len;
	if (data->minus == 1)
		minus_o(len, extra, hash, data);
}

void			conv_o(t_printf *data)
{
	unsigned long long	d;
	int					len;
	short				hash;

	hash = 0;
	d = va_arg(data->args, unsigned long long);
	d = typecast_u(data, d);
	if (data->hash == 1 && d != 0)
		hash = 1;
	len = ft_digcountbase_u(d, 8);
	flaghandler_o(data, len, hash, d);
}
