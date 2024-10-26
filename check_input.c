/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:05:50 by mmorais           #+#    #+#             */
/*   Updated: 2024/10/26 12:05:52 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	print_valid_params(void)
{
	char	*valid_params;

	valid_params = ""
		"Available options:\n"
		"--------------------------------------------------------------------\n"
		"\t./fractol mandelbrot\n"
		"\t./fractol julia <x> <y>\n"
		"\t./fractol julia -0.761682243 0.088785046\n"
		"--------------------------------------------------------------------\n";
	ft_putstr(valid_params);
}

static int	ft_is_double(const char *str)
{
	int	has_dot;
	int	has_digit;

	has_dot = 0;
	has_digit = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && (ft_isdigit(*str) || *str == '.'))
	{
		if (*str == '.')
		{
			if (has_dot)
				return (0);
			has_dot = 1;
		}
		else if (!ft_isdigit(*str))
			return (0);
		else
			has_digit++;
		str++;
	}
	if (!has_digit)
		return (0);
	return (1);
}

static int	check_input_2(char **av)
{
	if (ft_strncmp(av[1], "julia", 5) != 0)
	{
		ft_putstr("Error, invalid parameters.\n");
		print_valid_params();
		return (-1);
	}
	if (!ft_is_double(av[2]) || !ft_is_double(av[3]))
	{
		ft_putstr("Error, invalid parameters.\n");
		print_valid_params();
		return (-1);
	}
	return (2);
}

int	check_input(int ac, char **av)
{
	if (ac != 2 && ac != 4)
	{
		ft_putstr("Error, invalid parameters.\n");
		print_valid_params();
		return (-1);
	}
	else if (ac == 2 && ft_strncmp(av[1], "mandelbrot", 10) != 0)
	{
		ft_putstr("Error, invalid parameters.\n");
		print_valid_params();
		return (-1);
	}
	if (ac == 4)
	{
		if (check_input_2(av) == 2)
			return (2);
		else
			return (-1);
	}
	return (1);
}
