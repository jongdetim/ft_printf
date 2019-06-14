/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conv3.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/13 20:19:13 by tide-jon       #+#    #+#                */
/*   Updated: 2019/06/13 20:19:18 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

long long	typecast(t_printf *data, long long d)
{
	if (data->length == 'l')
		d = (long)d;
	if (data->length == '0')
		d = (int)d;
	if (data->length == 'c')
		d = (char)d;
	if (data->length == 'h')
		d = (short)d;
	return (d);
}
