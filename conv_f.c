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

void				conv_f(t_printf *data)
{
	char		*str;
	long double	d;

	d = va_arg(data->args, long double);
	str = ft_ftoa(d, 6);
	ft_putstr(str);
}