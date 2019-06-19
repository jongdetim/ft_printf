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
/*
int				float_digcount(long double n)
{
	int	count;

	count = 0;
	if (n == 0)
		count = 1;
	while (n <= -1 || n >= 1)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char		*itoa_after(long double n)
{
	int		digcount;
	char	*str;
	int		i;

	digcount = float_digcount(n);
	i = digcount - 1;
	str = (char*)malloc(sizeof(char) * (digcount + 1));
	if (!str)
		return (NULL);
	while (i >= 0)
	{
		str[i] = (n / (10 * i)) + '0';
		n = n / 10;
		i--;
	}
	str[digcount] = '\0';
	return (str);
}
*/
short			getafter(char **str, long double after, int afterpoint)
{
	int 	i;
	char	*zeros;
	char	*temp;
	short	increment;

	i = 0;
	zeros = ft_strnew(0);
	while (i < afterpoint + 1)
	{
		after *= 10;
		if (after < 1)
		{
			temp = zeros;
			zeros = ft_strjoin("0", zeros);
			free(temp);
		}
		i++;
	}
	*str = ft_strjoin(zeros, ft_itoa(after)); // <--  overflows with high enough precision!
	free(zeros);
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
	beforestr = ft_strjoin(beforestr, "."); // <- niet bij precision van 0 !
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

	before = (long long)f;
	after = f - before;
	increment = getafter(&str, after, afterpoint);
	str = getbefore(str, before, increment);

	return (str);
}
