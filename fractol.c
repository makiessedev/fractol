#include "fractol.h"

# define DBL_MAX	1.7976931348623157e+308
# define DBL_MIN	2.2250738585072014e-308

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

void    my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
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

int calc_zn(t_datas vars)
{
    t_complex z;
    //c = vars.c;
    //t_complex c = {vars.c2.x, vars.c2.y};
    
    

    if (vars.is_julia == 1)
    {
        //c = vars.c;
        z.x = vars.z.x;
        z.y = vars.z.y;
        vars.c = vars.c2;
    }
    else if (vars.is_julia == 0)
    {
        z.x = 0.0;
        z.y = 0.0;
    }


    /* z.x = vars.z.x;
        z.y = vars.z.y; */

     // {-0.761682243, 0.088785046};
    int i;

    i = 1;
    while (i < 100)
    {
        z = add(mult(z, z), vars.c);

        if ((z.x * z.x) + (z.y * z.y) >= 4.0)
            return (i * 0x03989e);
        i++;
    }
    return (0x000000);  
}

void    render_fractal(t_datas vars)
{
    //t_complex c = {-2.0,2.0};
    t_complex pixel = {-1.0, -1.0};
    double    scale;

    scale = ((4.0 * vars.zoom) / 800.0);
    while (++pixel.x < WIDTH)
    {
        vars.c.x = (pixel.x * scale) + vars.offset.x;
        vars.c.y = 2.0 + vars.offset.y;
        pixel.y = -1.0;
        while (++pixel.y < HEIGHT)
        {
            vars.z.x = vars.c.x;
            vars.z.y = vars.c.y;
            my_mlx_pixel_put(&vars.img, pixel.x, pixel.y, calc_zn(vars));
            vars.c.y -= scale;
        }
    }
    mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img.img, 0, 0);
}

int mouse_scroll(int keycode, int x, int y, t_datas *vars)
{
    (void)x;
    (void)y;
    if (keycode == Button4) // SCROLL_UP
        vars->zoom *= 0.9;
    else if (keycode == Button5) // SCROLL_DOWN
        vars->zoom *= 1.1;
    render_fractal(*vars);
    return (0);
}

int key_handler(int keycode, t_datas *vars)
{
    if (keycode == XK_Left)
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

double	ft_atoi_f_2(const char *str, double fraction, double result)
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
int main(int ac, char **av)
{
    t_datas	vars;

	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, WIDTH, WIDTH, "Fract-ol");
	vars.img.img = mlx_new_image(vars.mlx, WIDTH, WIDTH);
    vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);

    vars.zoom = 1;
    vars.offset.x = -2.0;
    vars.offset.y = 0.0;


    if (ac == 2 && ft_strncmp(av[1], "mandelbrot", 10) == 0)
    {
        vars.c.x = -2.0;
        vars.c.y = 2.0;
        vars.is_julia = 0;
        render_fractal(vars);
    }
    else if (ac == 4 && ft_strncmp(av[1], "julia", 5) == 0)
    {
        vars.c2.x = ft_atoi_f(av[2]);
        vars.c2.y = ft_atoi_f(av[3]);
        vars.is_julia = 1;
        render_fractal(vars);
    }
    else
        return (ft_putstr("Error: ./fractal <mandelbrot> || ./fractal <julia> <x> <y>\n"), 0);

    mlx_mouse_hook(vars.mlx_win, mouse_scroll, &vars);
    mlx_hook(vars.mlx_win, KeyPress, KeyPressMask, key_handler, &vars);
	mlx_loop(vars.mlx);

    return (0);
}