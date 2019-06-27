#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

int		main(void)
{
	int	orig;
	int mine;

  	mine = ft_printf("%.0p, %.p", 0, 0);
	orig = printf("%.0p, %.p", 0, 0);
	ft_putnbr(mine);
	write(1, "\n", 1);
	ft_putnbr(orig);
	write(1, "\n", 1);
//har 	*str;
//	str = ft_itoabase(ULONG_MAX, 8);
//	printf("%s", str);
	return (0);
}
