#include <stdio.h>

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

typedef struct 	s_data
{
	va_list	args;
	va_list	backup;
	int		precision;
	int		width;
	char	*format;
}				t_data;

t_data	*init_data(const char * restrict format)
{
	t_data	*data;

	data = (t_data*)malloc(sizeof(t_data));
	data->precision = 0;
	data->width = 0;
	data->format = ft_strdup(format);
	return(data);
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

void    save_int(t_data *data)
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
	if (*(data->format) == '$')
	{
		set_argnum(data, d);
		data->format++;
	}
	else if (data->precision == -1)
		data->precision = d;
	else
		data->width = d;
}

int     ft_printf(const char * restrict format, ...)
{
	t_data	*data;

	data = init_data(format);
	va_start(data->args, format);
	va_copy(data->backup, data->args);
    while (*(data->format))
    {
        if (*(data->format) == '%')
        {
            data->format++;
            if (*(data->format) == '%')
                write(1, "%%", 1);
            if (*(data->format) >= '0' && *(data->format) <= '9')
			{
				save_int(data);
			}
            if (*(data->format) == 's')
            {
				write(1, va_arg(data->args, char*), 1);
            }
        }
        else
        {
            write(1, (data->format), 1);
        }
        data->format++;
    }
    return (0);
}

int main(void)
{
    ft_printf("after %s comes %s\n", "b", "a");
    ft_printf("%5$s %2$s %1$s", "1", "2", "3", "4", "5", "6");
    return (0);
}
