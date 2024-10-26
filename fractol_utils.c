/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 10:50:43 by mmorais           #+#    #+#             */
/*   Updated: 2024/10/26 12:09:07 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	handle_close_window(t_datas *vars)
{
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}

static int	mouse_scroll(int keycode, int x, int y, t_datas *vars)
{
	(void)x;
	(void)y;
	if (keycode == Button4)
		vars->zoom *= 0.9;
	else if (keycode == Button5)
		vars->zoom *= 1.1;
	render_fractal(*vars);
	return (0);
}

static int	key_handler(int keycode, t_datas *vars)
{
	if (keycode == XK_Escape)
		handle_close_window(vars);
	else if (keycode == XK_Left)
		vars->offset.x += (0.5 * vars->zoom);
	else if (keycode == XK_Right)
		vars->offset.x -= (0.5 * vars->zoom);
	else if (keycode == XK_Down)
		vars->offset.y += (0.5 * vars->zoom);
	else if (keycode == XK_Up)
		vars->offset.y -= (0.5 * vars->zoom);
	render_fractal(*vars);
	return (0);
}

void	hooks_wrapper(t_datas vars)
{
	mlx_mouse_hook(vars.mlx_win, mouse_scroll, &vars);
	mlx_hook(vars.mlx_win, KeyPress, KeyPressMask, key_handler, &vars);
	mlx_hook (vars.mlx_win, 17, 0, handle_close_window, &vars);
	mlx_loop(vars.mlx);
}

void	mlx_init_datas(t_datas *vars)
{
	vars->mlx = mlx_init();
	vars->mlx_win = mlx_new_window(vars->mlx, WIDTH, WIDTH, "Fract-ol");
	vars->img.img = mlx_new_image(vars->mlx, WIDTH, WIDTH);
	vars->img.addr = mlx_get_data_addr(vars->img.img,
			&vars->img.bits_per_pixel,
			&vars->img.line_length, &vars->img.endian);
	vars->zoom = 1;
	vars->offset.x = -2.0;
	vars->offset.y = 0.0;
}
