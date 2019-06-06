#include <includeFILE>

int		get_conv(char c, t_data *data)
{
	if (data->type) == '0'
}

void	parse_arg(t_data *data)
{
	data->format++;
	while (*(data->format) != '\0' && get_conv(*(data->format), data) == 0)
	{
		if (*(data->format) == '.')
			data->dot = 1;
		if (*(data->format) >= '0' && *(data->format) <= '9')
		{
			save_int(data);
		}
		data->format++;
	}		
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