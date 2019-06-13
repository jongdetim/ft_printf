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

static int		ft_transferbase(unsigned long n, int i, int base)
{
	int	j;

	j = 0;
	while (j < i)
	{
		n = (n / base);
		j++;
	}
	while (j >= 0)
	{
		n = n % base;
		j--;
	}
	return (n);
}

static int		ft_digcountbase(unsigned long n, int base)
{
	int	count;

	count = 0;
	if (n == 0)
		count = 1;
	while (n != 0)
	{
		n = n / base;
		count++;
	}
	return (count);
}

static char			*ft_itoabase(unsigned long n, int base)
{
	int		digcount;
	char	*str;
	int		i;
	int		temp;

	i = 0;
	digcount = ft_digcountbase(n, base);
	str = (char*)malloc(sizeof(char) * (digcount + 1));
	if (!str)
		return (NULL);
	while (i < (digcount))
	{
		temp = ft_transferbase(n, digcount - (i) - 1, base);
		str[i] = temp <= 9 ? temp + '0' : temp - 10 + 'a';
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	conv_p(t_printf *data)
{
	unsigned long	addr;
	char			*str;
	char			*temp;

	addr = va_arg(data->args, unsigned long);
	temp = ft_itoabase(addr, 16);
	str = ft_strjoin("0x", temp);
	free(temp);
	ft_putstr(str);
	free(str);
}
