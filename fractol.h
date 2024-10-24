#include "./mlx_linux/mlx.h"
#include <X11/keysym.h>
#include <X11/X.h>

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
    double  zoom;
}	t_datas;

#define WIDTH 800
#define HEIGHT 800