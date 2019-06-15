/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/13 17:11:02 by tide-jon       #+#    #+#                */
/*   Updated: 2019/06/15 20:30:51 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	remove include
*/

#include <stdio.h>

void		dispatcher(t_printf *data)
{
	int		i;
	char	*str;

	str = "cspdiouxXf%";
	i = 0;
	while (str[i])
	{
		if (str[i] == data->type)
		{
			data->arr[i](data);
			break ;
		}
		i++;
	}
}

void		build_dispatcher(t_printf *data)
{
	data->arr[0] = conv_c;
	data->arr[1] = conv_s;
	data->arr[2] = conv_p;
	data->arr[3] = conv_d;
	data->arr[4] = conv_d;
	data->arr[5] = conv_o;
	data->arr[6] = conv_u;/*
	data->arr[7] = conv_x;
	data->arr[8] = conv_bigx;
	data->arr[9] = conv_f;
	data->arr[10] = conv_prcnt; */
}

void		init_data(t_printf *data)
{
	data->precision = 0;
	data->width = 0;
	data->type = '0';
	data->zero = 0;
	data->dot = 0;
	data->space = 0;
	data->hash = 0;
	data->minus = 0;
	data->plus = 0;
	data->seperator = 0;
	data->length = '0';
}

void	set_argnum(t_printf *data, int d)
{
	int i;

	i = 0;
	va_copy(data->args, data->backup);
	while (i < d - 1)
	{
		(void)va_arg(data->args, int);
		i++;
	}
}

/*
**	saves the found integer as width, argnum$ or .precision
*/

void		save_int(t_printf *data, int d)
{
	if (*(data->format) == '$')
	{
		set_argnum(data, d);
		data->format++;
	}
	else if (data->dot == 1)
		data->precision = d;
	else
		data->width = d;
	data->format--;
}

/*
**	processes integers after % and deal with '0' flag.
*/

void		process_int(t_printf *data)
{
	int		i;
	int		j;
	int		d;
	char	*s;

	i = 0;
	j = 0;
	while (data->format[i] >= '0' && data->format[i] <= '9')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		s[j] = *(data->format);
		data->format++;
		j++;
	}
	s[i] = '\0';
	d = ft_atoi(s);
	free(s);
	save_int(data, d);
}

/*
**	checks if conversion type has been found
**	if the current character is a conversion type it is saved in data->type
*/

int		get_conv(t_printf *data)
{
	if (data->type == '0')
	{
		if (ft_strchr("diouxXcspegf%", *(data->format)) != NULL)
		{
			data->type = *(data->format);
			return (1);
		}
		return (0);
	}
	else
	{
		return (1);
	}
}

/*
**	'b' = long long; 'c' = character
*/

void	get_length(t_printf *data)
{
	if (ft_strchr("lhL", *(data->format)) != NULL)
	{
		if (data->length == '0')
		{
			data->length = *(data->format);
		}
		else if (data->length == 'h')
			data->length = 'c';
		else if (data->length == 'l')
			data->length = 'b';
	}
}

void	parse_arg(t_printf *data)
{
	data->format++;
	while (*(data->format) != '\0' && get_conv(data) == 0)
	{
		if (*(data->format) == '.')
			data->dot = 1;
		if (*(data->format) == '*')
			data->width = va_arg(data->args, int);
		if (*(data->format) == ' ')
			data->space = 1;
		if (*(data->format) == '-')
			data->minus = 1;
		if (*(data->format) == '+')
			data->plus = 1;
		if (*(data->format) == '#')
			data->hash = 1;
		if (*(data->format) == '\'')
			data->seperator = 1;
		if (*(data->format) == '0' && data->dot == 0)
			data->zero = 1;
		if (*(data->format) >= '1' && *(data->format) <= '9')
			process_int(data);
		get_length(data);
		data->format++;
	}
	dispatcher(data);
}

void	parser(t_printf *data)
{
	while (*(data->format))
	{
		if (*(data->format) == '%')
		{
			init_data(data);
			parse_arg(data);
		}
		else
		{
			write(1, (data->format), 1);
			data->ret++;
		}
		if (*(data->format))
			data->format++;
	}
}

/*
**	test function to check for successful parsing of flags etc.
*/

void	parsing_test(t_printf *data)
{
	printf("precision is       %i\n", data->precision);
	printf("width is           %i\n", data->width);
	printf("conversion type is %c\n", data->type);
	printf("length is          %c\n", data->length);
	printf("return value is    %i\n", data->ret);
	printf("zero flag is       %i\n", data->zero);
	printf("dot flag is        %i\n", data->dot);
	printf("space flag is      %i\n", data->space);
	printf("hash flag is       %i\n", data->hash);
	printf("minus flag is      %i\n", data->minus);
	printf("plus flag is       %i\n", data->plus);
	printf("seperator flag is  %i\n", data->seperator);
	printf("next argument is   %i\n", va_arg(data->args, int));
}

/*
**	main function
*/

int			ft_printf(const char *restrict format, ...)
{
	t_printf	*data;

	data = (t_printf*)malloc(sizeof(t_printf));
	data->format = ft_strdup(format);
	data->ret = 0;
	build_dispatcher(data);
	va_start(data->args, format);
	va_copy(data->backup, data->args);
	parser(data);
	parsing_test(data);
	va_end(data->args);
	return (data->ret);
}

int			main(void)
{
//	ft_printf("this is a test:\n%+0d\n%d\n%d\n%-hd\n", 2000000000, 40000000, 40000000, (short)1000);
//	printf("this is a test:\n%20u\n%d\n%d\n%-hd\n", +2000000000, 40000000, 40000000, (short)1000);
	printf("%-10.02d\n%10.u\n%p\n", -0, 0, " ");
	ft_printf("%-10.2d\n%10.u\n%p\n", -0, 0, " ");
//	ft_printf("\n%3$*lls\n", "1", "2", 3, "4", "5", "6");
//	printf("%-10c", 'a');
	return (0);
}
