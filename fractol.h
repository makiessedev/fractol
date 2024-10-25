#include "./mlx_linux/mlx.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <unistd.h>

// to remove
#include <stdio.h>
#include <stdlib.h>

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_img;

typedef struct s_complex
{
    double x;
    double y;
} t_complex;

typedef struct s_datas
{
	void			*mlx;
	void			*mlx_win;
	t_img		img;
    t_complex   offset;
    double  zoom;
    int is_julia;
    t_complex c;
    t_complex c2;
    t_complex z;
}	t_datas;

#define WIDTH 800
#define HEIGHT 800

# define DBL_MAX	1.7976931348623157e+308
# define DBL_MIN	2.2250738585072014e-308

int ft_strncmp(char *s1, char *s2, int n);
void ft_putstr(char *s);
double	ft_atoi_f(const char *str);
int mouse_scroll(int keycode, int x, int y, t_datas *vars);
int key_handler(int keycode, t_datas *vars);
void    render_fractal(t_datas vars);