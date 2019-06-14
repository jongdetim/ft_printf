#include "libft.h"

#include <stdio.h>

int		ft_digcountbase(long long n, int base)
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
