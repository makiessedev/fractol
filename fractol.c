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

int main(void)
{
    t_datas	vars;
    t_complex c = {-2.0 ,2.0};
    t_complex pixel = {-1.0, -1.0};
    double   scale;

	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx ,800, 800, "Fract-ol");
	vars.img.img = mlx_new_image(vars.mlx, 800, 800);
    vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);

    scale = (4.0 * 0.95) / 800.0;
    while (++pixel.x < 800)
    {
        c.y = 2.0;
        pixel.y = -1.0;
        while (++pixel.y < 800)
        {
            my_mlx_pixel_put(&vars.img, pixel.x, pixel.y, calc_zn(c));
            c.y -= scale;
        }
         c.x += scale;
       
    }
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img.img, 0, 0);
	mlx_loop(vars.mlx);
}