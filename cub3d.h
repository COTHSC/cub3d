#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>
#include <math.h>
#include "mlx_linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct  s_img {
	void        *ptr;
	char        *data;
	int         width;
	int         height;

	int         bpp;
	int         size_l;
	int         endian;
}			t_img;

typedef struct  s_pos {
	double          posX;
	double          posY;
	double          dirX;
	double          dirY;
	double          planeX;
	double          planeY;
	double          move_speed;
	double          rot_speed;
}                       t_pos;

typedef struct  s_vars {
	void        *mlx;
	void        *win;
	t_pos           *pos;
	t_img           *img;
}               t_vars;

void		pixel_put(t_img *image, int x, int y, int color);
void		line_put(t_img *img, int x, int start, int end, int color);
int		render_next_frame(t_vars *vars);


#endif

