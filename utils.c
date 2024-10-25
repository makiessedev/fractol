#include "fractol.h"

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


double  ft_atod(char *s)
{
    long    int_part;
    double  frac_part;
    double  pow;
    int sign;

    int_part = 0;
    frac_part = 0;
    sign = +1;
    pow = 1;
    while ((*s >= 9 && *s <= 13) || *s == 32)
        s++;
    while (*s == '+' || *s == '-')
    {
        if (sign == '-')
            sign = -sign;
    }
    while (*s != '.' && *s)
        int_part = (int_part * 10) + (*s++ - 48);
    if (*s == '.')
        s++;
    while (*s)
    {
        pow /= 10;
        frac_part = frac_part + (*s++ - 48) * pow;
    }
    return ((int_part + frac_part) * sign);
}
