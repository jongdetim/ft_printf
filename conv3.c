/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conv3.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/13 20:19:13 by tide-jon       #+#    #+#                */
/*   Updated: 2019/06/18 15:49:37 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>

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

char			*ft_strtoupper(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if ('a' <= str[i] && str[i] <= 'z')
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}

char			*getafter(long double after, int afterpoint)
{
	int 	i;
	char	*str;

	i = 0;
	while (i < afterpoint + 1)
	{
		after *= 10;
		i++;
	}
	str = ft_itoa((long long)after);
	i = afterpoint - 1;
	if (str[afterpoint] >= 5)
	{
		if (str[i] < '9')
			str[i]++;
		else
			str[i] = '0';
		while (str[i] == '0')
		{
			i--;
			if (str[i] < '9')
				str[i]++;
			else
				str[i] = '0';
		}
	}
	return (str);
}

char			*ft_ftoa(long double f, int afterpoint)
{
	char		*str;
	long double	before;
	long double	after;

	before = (long long)f;
	after = f - before;
	str = getafter(after, afterpoint);
	return (str);
}
