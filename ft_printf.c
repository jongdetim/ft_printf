#include <stdio.h>

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef struct 	s_data
{
	va_list	args;
	va_list	backup;
	int		precision;
	int		width;
	char	*format;
	char	type;
	int		ret;
	int		zero;
	int		dot;
	int		space;
	int		hash;
	int		minus;
	int		plus;
	int		seperator;
}				t_data;


void	*init_data(t_data *data)
{
	data->precision = 0;
	data->width = 0;
	data->type = '0';
	data->ret = 0;
	data->zero = 0;
	data->dot = 0;
	data->space = 0;
	data->hash = 0;
	data->minus = 0;
	data->plus = 0;
	data->seperator = 0;
}

void	set_argnum(t_data *data, int d)
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

// saves the found integer as width, argnum$ or .precision

void	save_int(t_data *data, int d)
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

// processes integers after % and deal with '0' flag.

void    process_int(t_data *data)
{
	int i;
	int j;
	int d;
	char *s;

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

int		get_conv(char c, t_data *data)
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

void	parse_arg(t_data *data)
{
	data->format++;
	while (*(data->format) != '\0' && get_conv(*(data->format), data) == 0)
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
		data->format++;
	}
//	process_arg(t_data *data);
}

void	parser(t_data *data)
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

void	parsing_test(t_data *data)
{
	printf("precision is %i\n", data->precision);
	printf("width is %i\n", data->width);
	printf("conversion type is %c\n", data->type);
	printf("return value is %i\n", data->ret);
	printf("zero flag is %i\n", data->zero);
	printf("dot flag is %i\n", data->dot);
	printf("space flag is %i\n", data->space);
	printf("hash flag is %i\n", data->hash);
	printf("minus flag is %i\n", data->minus);
	printf("plus flag is %i\n", data->plus);
	printf("seperator flag is %i\n", data->seperator);
	printf("next argument is %s\n", va_arg(data->args, int));
}

/*
**	main function
*/

int     ft_printf(const char * restrict format, ...)
{
	t_data	*data;

	data = (t_data*)malloc(sizeof(t_data));
	data->format = ft_strdup(format);
	va_start(data->args, format);
	va_copy(data->backup, data->args);
	parser(data);
	parsing_test(data);
	va_end(data->args);
    return (0);
}

int main(void)
{
//	ft_printf("this is a test:\n%#-+'0*.1sk\n", 5, "3");
//	ft_printf("\n%3$*s\n", "1", "2", 3, "4", "5", "6");
	printf("%Lhi", 10000000);
    return (0);
}
