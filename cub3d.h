#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>
#include <math.h>
#include "mlx_linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24
#define texHeight 64
#define texWidth 64
#define FCOLOR 0x0000FF00
#define CCOLOR 0x00FFFFFF

typedef struct	s_keys {
	int	w;
	int	a;
	int	s;
	int	d;
	int	l;
	int	r;
}		t_keys;


typedef struct  s_img {
	void        *ptr;
	int	*data;
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
	void	*mlx;
	void	*win;
	t_pos	*pos;
	t_img	*img;
	t_img	*text[8];
	t_keys	*keys;
	int	buf[480][640];
}               t_vars;

void		pixel_put(t_img *image, int x, int y, int color);
void		line_put(t_img *img, int x, int start, int end, int color);
int		render_next_frame(t_vars *vars);
void		reset_buffer(t_vars *vars);
int     	draw_floor(t_vars *vars, int x, int draw_end);
int		draw_cieling(t_vars *vars, int x, int draw_start);
int    key_release(int keycode, t_vars *vars);
int    key_press(int keycode, t_vars *vars);

#endif
