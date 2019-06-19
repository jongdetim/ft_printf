/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conv_f.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/17 19:56:57 by tide-jon       #+#    #+#                */
/*   Updated: 2019/06/18 15:58:25 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>

void				conv_f(t_printf *data)
{
	char		*str;
	long double	d;

	if (data->length == 'L')
	{
		d = va_arg(data->args, long double);
//		__mingw_printf("long double %Lf", d);
	}
	else
	{
		d = va_arg(data->args, double);
//		__mingw_printf("double %.8Lf\n", d);
	}
	if (data->dot)
		str = ft_ftoa(d, data->precision);
	else
		str = ft_ftoa(d, 6);
	ft_putstr(str);
}
