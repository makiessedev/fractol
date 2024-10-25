#include "fractol.h"

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