#include <unistd.h>
#include <stdarg.h>

int	ft_putnbr(long nb, int base)
{
	char	*base_set = "0123456789abcdef";
	int		count = 0;

	if (nb < 0)
	{
		count += write(1, "-", 1);
		nb = -nb;
	}
	if (nb >= base)
		count += ft_putnbr(nb / base, base);
	count += write(1, &base_set[nb % base], 1);
	return (count);
}

int	ft_putstr(char *str)
{
	int	count = 0;

	if (!str)
		str = "(null)";
	while (*str)
		count += write(1, str++, 1);
	return (count);
}

int	ft_printf(char *str, ...)
{
	va_list	ap;
	int		count = 0;

	va_start(ap, str);
	while (*str)
	{
		if (*str == '%' && *(str + 1))
		{
			str++;
			if (*str == 'd')
				count += ft_putnbr(va_arg(ap, int), 10);
			else if (*str == 'x')
				count += ft_putnbr(va_arg(ap, unsigned int), 16);
			else if (*str == 's')
				count += ft_putstr(va_arg(ap, char *));
		}
		else
			count += write(1, str, 1);
		str++;
	}
	va_end(ap);
	return (count);
}

