#include "fractol.h"

void    my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int calc_zn(t_complex c)
{
    t_complex temp;
    t_complex z = {0.0, 0.0};
    int i;

    i = 1;
    while (i < 120)
    {
        temp.x = (z.x * z.x) - (z.y * z.y) + c.x;
        temp.y = 2 * z.x * z.y + c.y;
        z = temp;

        if ((z.x * z.x) + (z.y * z.y) >= 4.0)
            return (i * 0x03989e);
        i++;
    }
    return (0x000000);
    
}

void    render_fractal(t_datas vars)
{
    t_complex c = {-2.0 ,2.0};
    t_complex pixel = {-1.0, -1.0};
    double    scale;

    scale = (4.0 * vars.zoom) / 800.0;
    while (++pixel.x < WIDTH)
    {
        c.y = 2.0;
        pixel.y = -1.0;
        while (++pixel.y < HEIGHT)
        {
            my_mlx_pixel_put(&vars.img, pixel.x, pixel.y, calc_zn(c));
            c.y -= scale;
        }
         c.x += scale;
    }
    mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img.img, 0, 0);
}

int mouse_scroll(int keycode, int x, int y, t_datas *vars)
{
    (void)x;
    (void)y;
    if (keycode == 4) // SCROLL_UP
    {
        vars->zoom *= 0.9;
    }
    else if (keycode == 5) // SCROLL_DOWN
    {
        vars->zoom *= 1.1;
    }
    render_fractal(*vars);
    return (0);
}

int main(void)
{
    t_datas	vars;
    

	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx ,WIDTH, WIDTH, "Fract-ol");
	vars.img.img = mlx_new_image(vars.mlx, WIDTH, WIDTH);
    vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);

    vars.zoom = 1;

    render_fractal(vars);
    /* mlx_hook(vars.mlx_win, 5, 0, mouse_scroll, &vars);
    mlx_hook(vars.mlx_win, 4, 0, mouse_scroll, &vars); */
    mlx_mouse_hook(vars.mlx_win, mouse_scroll, &vars);
	mlx_loop(vars.mlx);
}