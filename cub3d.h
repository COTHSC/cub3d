/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 10:16:16 by jescully          #+#    #+#             */
/*   Updated: 2021/04/02 10:37:06 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>
# include <math.h>
# include "mlx_linux/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# define FCOLOR 0x0000FF00
# define CCOLOR 0x00FFFFFF

typedef struct	s_raysprite
{
	double		sx;
	double		sy;
	double		invd;
	double		tx;
	double		ty;
	int			ssx;
	int			dsx;
	int			dsy;
	int			dey;
	int			dex;
	int			sheight;
	int			swidth;
	int			i;
	int			num_sprite;
	double		*zbuffer;
}				t_raysprite;

typedef struct	s_raycast
{
	int			i;
	double		camx;
	double		rdirx;
	double		rdiry;
	double		wx;
	double		stp;
	double		texp;
	int			texx;
	int			texy;
	int			mapx;
	int			mapy;
	double		sdx;
	double		sdy;
	double		ddx;
	double		ddy;
	double		pwd;
	int			stpx;
	int			stpy;
	int			lineh;
	int			draws;
	int			drawe;
}				t_raycast;

typedef struct	s_keys {
	int			w;
	int			a;
	int			s;
	int			d;
	int			l;
	int			r;
}				t_keys;

typedef struct	s_res {
	int			w;
	int			h;
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		*S;
	int			C;
	int			F;
	int			count;
}				t_res;

typedef int	(*t_fptr)(t_res *, char *);

typedef struct	s_texpath {
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
}				t_texpath;

typedef struct	s_sprites {
	double		x;
	double		y;
	int			texture;
	double		dist;
}				t_sprites;

typedef struct	s_img {
	void		*ptr;
	int			*data;
	int			width;
	int			height;
	int			bpp;
	int			size_l;
	int			endian;
}				t_img;

typedef struct	s_pos {
	double		px;
	double		py;
	double		dx;
	double		dy;
	double		plx;
	double		ply;
	double		ms;
	double		rs;
}				t_pos;

typedef struct	s_needs_freedom {
	int			mlx;
	int			win;
	int			p;
	int			img;
	int			text[8];
	int			sprite;
	int			sprites;
	int			keys;
	int			res;
	int			map;
	int			collumn;
	int			map_h;
	int			save;
	int			error;
	int			farray;
}				t_needs_freedom;

typedef struct		s_vars {
	void			*mlx;
	void			*win;
	t_pos			*p;
	t_img			*img;
	t_img			*text[8];
	t_img			*sprite;
	t_sprites		**sprites;
	t_keys			*keys;
	t_res			*res;
	int				*map;
	int				*collumn;
	int				map_h;
	int				save;
	char			**error;
	char			**farray;
	t_needs_freedom	*to_free;
}					t_vars;

void	pixel_put(t_img *image, int x, int y, int color);
void	line_put(t_img *img, int x, int start, int end, int color);
int		render_next_frame(t_vars *vars);
void	reset_buffer(t_vars *vars);
int		draw_floor(t_vars *vars, int x, int draw_end);
int		draw_cieling(t_vars *vars, int x, int draw_start);
int		key_release(int keycode, t_vars *vars);
int		key_press(int keycode, t_vars *vars);
int		button_press(int buttoncode, t_vars *vars);
int		init_position(t_vars *vars);
void	draw(t_vars *vars);
int		key_hook(t_vars *vars);
void	draw_frame(t_vars *vars);
int		map_to_struct(int *map, t_vars *vars);
int		spritecaster(t_vars *vars, int texx, int texy, double *zbuffer);
int		spritefinder(t_sprites **sprite, t_vars *vars);
int		get_next_line(int const fd, char **line);
int		parse_resolution(t_res *res, char *buf);
int		parse_lines(t_vars *vars, int fd);
int		parse_paths(t_res *res, char *buf);
int		parse_sprite(t_res *res, char *buf);
int		parse_colors(t_res *res, char *buf);
int		ft_get_color(int r, int g, int b);
int		parse_map(t_vars *vars, int fd);
int		sia(int *array, int h);
void	innit_keys(t_vars *vars);
int		get_value(t_vars *vars, int h, int w);
void	check_map(t_vars *vars);
int		init_sprites(t_vars *vars);
int		free_sprites(t_vars *vars);
int		exit_game(t_vars *vars, int bol, int error);
int		save_img(t_vars *vars);
int		init_sprites(t_vars *vars);
int		free_sprites(t_vars *vars);
int		count_sprites(t_vars *vars);
int		sprite_sort(t_sprites **sprite, int num_sprites);
void	swap_sprites(t_sprites *sprite1, t_sprites *sprite2);
void	prep_image(t_vars *vars);
int		get_texnum(t_raycast *r, int side);
void	init_dirs(t_vars *vars, t_raycast *r);
int		calc_line_height(t_vars *vars, t_raycast *r, int side);
int		check_struct(t_res *res);
int		empty_line(char *str);
int		ft_isspace(char c);
void	free_farray(char **farray);
int		innit_arrayf(t_fptr functions[8], t_vars *vars);
int		ft_get_color(int r, int g, int b);
void	*ft_realloc(void *ptr, int size, int newsize);
int		array_length(int *array);
int		sia(int *array, int h);
int		realloc_map(t_vars *vars, int length, int h);
int		save_position(t_vars *vars, char c, int h, int i);
int		init_orientation(t_vars *vars, double h);
void	check_max_screen_size(t_vars *vars);
void	init_error(t_vars *vars);
void	little_free(t_vars *vars);
void	big_free(t_vars *vars);
void	path_sorter(t_res *res, char *buf, int start, int length);
int		parse_map_string(t_vars *vars, char *buf, int h, int *j);
int		ft_advance(char *buf, int *r, int *g, int *b);
void	i_through_space(char *str, int *i);

#endif
