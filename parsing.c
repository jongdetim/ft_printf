#include <printf.h>

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
			data->format++;
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
		if (*(data->format) >= '0' && *(data->format) <= '9')
			process_int(data);
		data->format++;
	}
	process_arg(t_data *data);
}

void	parser(t_data *data)
{
	while (*(data->format))
    {
        if (*(data->format) == '%')
        {
			parse_arg(data);
        }
        else
        {
            write(1, (data->format), 1);
			data->return++;
        }
        data->format++;
    }
}
