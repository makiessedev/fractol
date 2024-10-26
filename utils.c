/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 07:47:27 by mmorais           #+#    #+#             */
/*   Updated: 2024/10/26 09:40:59 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_strncmp(char *s1, char *s2, int n)
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

void	ft_putstr(char *s)
{
	int	i;

	if (s == NULL)
		return ;
	i = -1;
	while (s[++i])
		write (1, &s[i], 1);
}

t_complex	add(t_complex a, t_complex b)
{
	t_complex	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return (res);
}

t_complex	mult(t_complex a, t_complex b)
{
	t_complex	res;

	res.x = (a.x * b.x) - (a.y * b.y);
	res.y = (a.x * b.y) + (a.y * b.x);
	return (res);
}
