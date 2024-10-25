#include "fractol.h"

void    my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int calc_zn(t_datas vars)
{
    t_complex z;
    t_complex temp;
    int i;

    if (vars.is_julia == 1)
    {
        z.x = vars.z.x;
        z.y = vars.z.y;
        vars.c = vars.c2;
    }
    else if (vars.is_julia == 0)
    {
        z.x = 0.0;
        z.y = 0.0;
    }

    i = 1;
    while (i < 100)
    {
        temp.x = (z.x * z.x) - (z.y * z.y) + vars.c.x;
        temp.y = 2 * z.x * z.y + vars.c.y;
        z = temp;

        if ((z.x * z.x) + (z.y * z.y) >= 4.0)
            return (i * 0x03989e);
        i++;
    }
    return (0x000000);  
}

void    render_fractal(t_datas vars)
{
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