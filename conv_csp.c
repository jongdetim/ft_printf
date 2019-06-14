/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conv1.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/13 20:19:15 by tide-jon       #+#    #+#                */
/*   Updated: 2019/06/13 22:58:53 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	conv_c(t_printf *data)
{
	int		i;
	char	c;

	i = 1;
	c = va_arg(data->args, int);
	if (data->minus == 1)
		write(1, &c, 1);
	while (i < data->width)
	{
		write(1, " ", 1);
		i++;
	}
	if (data->minus == 0)
		write(1, &c, 1);
}

void	conv_s(t_printf *data)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup((const char*)va_arg(data->args, char*));
	if ((int)ft_strlen(str) > data->precision)
		str[data->precision] = '\0';
	if (data->minus == 1)
		ft_putstr((const char*)str);
	while (i < data->width - (int)strlen(str))
	{
		write(1, " ", 1);
		i++;
	}
	if (data->minus == 0)
		ft_putstr((const char*)str);
	free(str);
}

void	conv_p(t_printf *data)
{
	unsigned long	addr;
	char			*str;
	char			*temp;
	int				i;

	i = 0;
	addr = va_arg(data->args, unsigned long);
	temp = ft_itoabase(addr, 16);
	str = ft_strjoin("0x", temp);
	free(temp);
	while (data->width > i + ft_strlen(str) && data->minus == 0)
	{
		write(1, " ", 1);
		i++;
	}
	ft_putstr(str);
	while (data->width > i + ft_strlen(str) && data->minus == 1)
	{
		write(1, " ", 1);
		i++;
	}
	free(str);
}
