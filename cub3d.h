#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>
#include "mlx_linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define mapWidth 24
#define mapHeight 24
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


typedef struct	s_res {
    int	w;
    int	h;
    char *NO;
    char *SO;
    char *WE;
    char *EA;
    char *S;
    int  C;
    int  F;
}		t_res;

typedef int (*fptr)(t_res *, char *);

typedef struct	s_texpath {
    char *NO;
    char *SO;
    char *WE;
    char *EA;
}		t_texpath;

typedef struct	s_sprites {
    double  x;
    double  y;
    int     texture;
    double  dist;
}		t_sprites;

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
    double          px;
    double          py;
    double          dx;
    double          dy;
    double          plx;
    double          ply;
    double          ms;
    double          rs;
}                       t_pos;

typedef struct  s_vars {
    void	    *mlx;
    void	    *win;
    t_pos	    *p;
    t_img	    *img;
    t_img	    *text[8];
    t_img	    *sprite;
    t_sprites   **sprites;
    t_keys	    *keys;
    t_res	    *res;
    int		    **buf;
    int		    **WorldMap;
    int		    *map;
    int		    *collumn;
    int	    	map_h;
}               t_vars;

void		pixel_put(t_img *image, int x, int y, int color);
void		line_put(t_img *img, int x, int start, int end, int color);
int		render_next_frame(t_vars *vars);
void		reset_buffer(t_vars *vars);
int     	draw_floor(t_vars *vars, int x, int draw_end);
int		draw_cieling(t_vars *vars, int x, int draw_start);
int    key_release(int keycode, t_vars *vars);
int    key_press(int keycode, t_vars *vars);
int     button_press(int buttoncode, t_vars *vars);
int     init_position(t_vars *vars);
void    draw(t_vars *vars);
int             key_hook(t_vars *vars);
int		draw_frame(t_vars *vars);
int map_to_struct(int *map, t_vars *vars);
int     spritecaster(t_vars *vars, int texX, int texY, int *zbuffer);
int     spritefinder(t_sprites **sprite, t_vars *vars);
int			get_next_line(int const fd, char **line);
int     parse_resolution(t_res *res, char *buf);
int     parse_lines(t_vars *vars, int fd);
int     parse_paths(t_res *res, char *buf);
int     parse_sprite(t_res *res, char *buf);
int     parse_colors(t_res *res, char *buf);
int     ft_get_color(int r, int g, int b);
int     parse_map(t_vars *vars, char *buf, int h);
int     sia(int *array, int h);
void    innit_keys(t_vars *vars);
int     get_value(t_vars *vars, int h, int w);
int     check_map(t_vars *vars);
int     init_sprites(t_vars *vars);
 int     free_sprites(t_vars *vars);
 int exit_game(t_vars *vars);
int save_img(t_vars *vars,const char* fichier);
#endif
