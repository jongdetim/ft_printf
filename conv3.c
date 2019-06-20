/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conv3.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/13 20:19:13 by tide-jon       #+#    #+#                */
/*   Updated: 2019/06/20 19:50:13 by tide-jon      ########   odam.nl         */
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

short			ftoa_round(int i, char *str)
{
	if ((str)[i + 1] >= '5')
	{
		if (str[i] < '9')
			str[i]++;
		else
			str[i] = '0';
		while (str[i] == '0' && i > 0)
		{
			i--;
			if (str[i] < '9')
				str[i]++;
			else
				str[i] = '0';
		}
		if (i == 0 && str[i] == '0')
			return (1);
		else
			return (0);
	}
	return (0);
}

short			getafter(char **str, long double after, int afterpoint)
{
	int 		i;
	char		*temp;
	char		*temp2;
	short		increment;
	long long	num;

	i = 0;
	*str = ft_strnew(0);
	while (i < afterpoint + 1)
	{
		temp = *str;
		after *= 10;
		num = (long long)after;
		temp2 = ft_itoa(num);
		*str = ft_strjoin(*str, temp2);
		after -= num;
		free(temp);
		free(temp2);
		i++;
	}
	i = afterpoint - 1;
	increment = ftoa_round(i, *str);
	(*str)[afterpoint] = '\0';
	return (increment);
}

char			*getbefore(char *str, long double before, short increment)
{
	char		*beforestr;
	char		*temp;

	if (before >= 0)
		before += increment;
	else
		before -= increment;
	beforestr = ft_itoa(before);
	temp = beforestr;
	beforestr = ft_strjoin(beforestr, ".");
	free(temp);
	temp = str;
	str = ft_strjoin(beforestr, str);
	free(temp);
	return (str);
}

char			*ft_ftoa(long double f, int afterpoint)
{
	char		*str;
	long double	before;
	long double	after;
	short		increment;
	char		*temp;

	before = (long long)f;
	if (f < 0)
		after = (f - before) * -1;
	else
		after = f - before;
	increment = getafter(&str, after, afterpoint);
	str = getbefore(str, before, increment);
	if ((f < 0 && before == 0) || (f == 0 && 1 / f < 0))
	{
		temp = str;
		str = ft_strjoin("-", str);
		free(temp);
	}
	return (str);
}
