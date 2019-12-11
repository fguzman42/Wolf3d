/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 16:47:56 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/12/04 13:14:27 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define WIDTH 24
# define HEIGHT 24
# define S_WIDTH 1000
# define S_HEIGHT 700
# define texwidth 64

# include <math.h>
# include <stdio.h>
# include "../libft/includes/libft.h"
# include "../minilibx_macos/mlx.h"

typedef struct			s_intslide{
	int					*xslide;
	int					size;
	struct s_intslide	*next;
}						t_slide;

typedef struct 			s_texture
{
	int					x;
	int 				y;
	int 				wall_x;
	int					wall_y;
	int					num;
}						t_texture;

typedef struct			s_grid{
	int					**map;
	int					xsize;
	int					ysize;
}						t_grid;

typedef struct			s_mlx{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	void				*xpm;
	int					sline;
	int					endian;
	int					bpp;
	int					*colors;
	int					**map;
	char				*tex[10];
	char				*pixs;
	struct s_p_coords	*v;
}						t_mlx;

typedef struct			s_vectors{
	double				X;
	double				Y;
}						t_vectors;

typedef	struct 			s_point{
	int					x;
	int					y;
}						t_point;

typedef	struct			s_trigger{
	int					hit;
	int					side;
}						t_trigger;

typedef struct 			s_proj_ray{
	int					drawStart;
	int					drawEnd;	
}						t_proj_ray;

typedef struct			s_dist{
	struct s_vectors	sideDist;
	struct s_vectors	deltaDist;
	double				perpWallDist;
}						t_dist;

typedef struct			s_tex
{
	double				wall_x;
	int					tex_x;
	int					tex_y;
	int					d;
	double				floor_x;
	double				floor_y;
	double				distWall;
	double				distPlayer;
	double				currentDist;
	double				weight;
	double				cfloor_x;
	double				cfloor_y;
	int					floortex_x;
	int					floortex_y;
	int					start;
	int					end;
}						t_tex;			

typedef struct			s_p_coords{
	struct s_vectors	pos;
	struct s_vectors	dir;
	struct s_vectors	plane;
	struct s_vectors	rayDir;
	struct s_point		map;
	struct s_point		step;
	t_tex				tex;
	t_dist				d;
	double				time;
	double				oldTime;
	int					lineHeight;
}						t_p_coords;

void				pxto_win(int x, int y, int color, t_mlx *mlx);
int					**give_map();
int					*colors(void);
int					deal_key(int key, t_mlx *mlx);

void				cast_all_rays(t_p_coords *v, int **map, t_mlx *mlx);
void				pxto_win(int x, int y, int color, t_mlx *mlx);
void				do_DDA(t_p_coords *v, t_dist *d, t_trigger *t, int **map);
void				get_direction(t_p_coords *v, t_dist *d);
void				mapping(t_p_coords *v, int **ma, t_proj_ray *curr, t_trigger *t);
void				drawSlide(int x, t_proj_ray *curr, t_trigger *t, t_p_coords *v,  t_mlx *mlx);
int					keys(int key, t_mlx *mlx);
int					redx(t_mlx *mlx);
int					release(int key, t_mlx *mlx);
int					press(int key, t_mlx *mlx);
#endif
