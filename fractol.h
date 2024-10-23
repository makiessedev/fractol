#include "./mlx_linux/mlx.h"

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
	t_complex		c;
	t_complex		lim;
}	t_datas;