/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 08:06:33 by mmorais           #+#    #+#             */
/*   Updated: 2024/10/26 10:47:37 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FRACTOL_H
# define FRACTOL_H

# include "./minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <unistd.h>

// to remove
# include <stdio.h>
# include <stdlib.h>

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_complex
{
	double	x;
	double	y;
}	t_complex;

typedef struct s_datas
{
	t_img		img;
	t_complex	offset;
	t_complex	c;
	t_complex	c2;
	t_complex	z;
	void		*mlx;
	void		*mlx_win;
	double		zoom;
	int			is_julia;
}	t_datas;

# define WIDTH 800
# define HEIGHT 800

# define DBL_MAX	1.7976931348623157e+308
# define DBL_MIN	2.2250738585072014e-308

void		render_fractal(t_datas vars);
void		ft_putstr(char *s);
void		hooks_wrapper(t_datas vars);
void		mlx_init_datas(t_datas *vars);
double		ft_atoi_f(const char *str);
int			ft_strncmp(char *s1, char *s2, int n);
int			mouse_scroll(int keycode, int x, int y, t_datas *vars);
int			key_handler(int keycode, t_datas *vars);
int			handle_close_window(t_datas *vars);
int			ft_isdigit(char c);
int			check_input(int ac, char **av);
t_complex	add(t_complex a, t_complex b);
t_complex	mult(t_complex a, t_complex b);
#endif
