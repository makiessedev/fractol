#include "fractol.h"

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int ft_strncmp(char *s1, char *s2, int n)
{
    if (s1 == NULL || s2 == NULL || n <= 0)
        return (0);
    while (*s1 == *s2 && n > 0 && *s1 != '\0')
    {
        s1++;
        s2++;
        n--;
    }
    return (*s1 - *s2);
}

void ft_putstr(char *s)
{
    int i;

    if (s == NULL)
        return ;
    i = -1;
    while (s[++i])
        write (1, &s[i], 1);
}

static double	ft_atoi_f_2(const char *str, double fraction, double result)
{
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			result = result + ((*str++) - '0') * fraction;
			fraction /= 10;
		}
	}
	return (result);
}

double	ft_atoi_f(const char *str)
{
	double	result;
	double	fraction;
	int		sign;

	sign = 1;
	result = 0.0;
	fraction = 0.1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		if (result * sign > DBL_MAX)
			return (DBL_MAX);
		if (result * sign < -DBL_MAX)
			return (-DBL_MAX);
		str++;
	}
	result = ft_atoi_f_2(str, fraction, result);
	return (result * sign);
}