/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 10:50:24 by mmorais           #+#    #+#             */
/*   Updated: 2024/10/26 11:00:40 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
