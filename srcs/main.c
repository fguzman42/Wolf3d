/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:56:36 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/12/04 11:55:02 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	init(t_mlx *mlx, t_p_coords *v)
{
	int x;
	int y;

	x = 64;
	y = 64;
	v->pos.X = 22;
	v->pos.Y = 11.5;// 12;  //x and y start position
	v->dir.X = -1; 
	v->dir.Y = 0; //initial direction vector
	v->plane.X = 0;
	v->plane.Y = 0.66; //the 2d raycaster version of camera plane
	v->time = 0; //time of current frame
	v->oldTime = 0; //time of previous frame
	
	mlx->mlx_ptr = mlx_init();
	mlx->colors = colors();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, S_WIDTH, S_HEIGHT, "wolf3d");
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, S_WIDTH, S_HEIGHT);
	mlx->pixs = mlx_get_data_addr(mlx->img_ptr, &mlx->bpp,\
	&mlx->sline, &mlx->endian);
	mlx->xpm = mlx_xpm_file_to_image(mlx->mlx_ptr, "./pics/wood.xpm", &x, &y);
	printf("first element of xpm == %d\n", *(int *)mlx->xpm);
}

void	cast_all_rays(t_p_coords *v, int **map, t_mlx *mlx)
{
	int			x;
	int 		color;
	double		cameraX;
	// double		rayDirX;
	// double		rayDirY;
	t_proj_ray	curSlide;
	t_trigger	t;
	int bpp;
	int sline;
	int endian;
	int i;


	i = 0;
	x = 0;
	mlx->tex[0] = mlx_get_data_addr(mlx->xpm, &bpp, &sline, &endian);

	while (x < S_WIDTH)
	{
    	cameraX = 2 * x / (double)S_WIDTH - 1;
		v->rayDir.X = v->dir.X + v->plane.X * cameraX;
		v->rayDir.Y = v->dir.Y + v->plane.Y * cameraX;
		mapping(v, map, &curSlide, &t);
		// printf("%d val \n", map[v->map.x][v->map.y]);
		color = *((int *)mlx->tex[0]);//mlx->colors[map[v->map.x][v->map.y] - 1];
		// printf("hereman\n");

		if (t.side == 1)
			color /= 2;
		drawSlide(x, &curSlide, &t, v, mlx);
		x++;

	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}


void	tex_calc(t_trigger *t, t_p_coords *v)
{

	if (t->side == 0)
		v->tex.wall_x = v->pos.Y + v->d.perpWallDist * v->rayDir.Y;
	else
		v->tex.wall_x = v->pos.X + v->d.perpWallDist * v->rayDir.X;
		v->tex.wall_x -= floor((v->tex.wall_x));
		v->tex.tex_x = (int)(v->tex.wall_x * (double)(64));
	if (t->side == 0 && v->rayDir.X > 0)
		v->tex.tex_x = 64 - v->tex.tex_x - 1;
	if (t->side == 1 && v->rayDir.Y	< 0)
		v->tex.tex_x = 64 - v->tex.tex_x - 1;	
}


void	floor_tex(int x, t_p_coords *v, t_mlx *mlx)
{
	int y;
	int y_end;

	y = v->tex.start;
	y_end = v->tex.end;
	v->tex.distWall = v->d.perpWallDist;
	v->tex.distPlayer = 0.0;
	if (y_end < 0)
		y_end = S_HEIGHT;
	y = y_end + 1;
	while (y < S_HEIGHT)
	{
		v->tex.currentDist = S_HEIGHT / (2.0 * y - S_HEIGHT);
		v->tex.weight = (v->tex.currentDist - v->tex.distPlayer) / (v->tex.distWall - v->tex.distPlayer);
		v->tex.cfloor_x = v->tex.weight * v->tex.floor_x + (1.0 - v->tex.weight) * v->pos.X;
		v->tex.cfloor_y = v->tex.weight * v->tex.floor_y + (1.0 - v->tex.weight) * v->pos.Y;
		v->tex.tex_x = (int)(v->tex.cfloor_x * 64) % 64;
		v->tex.tex_y = (int)(v->tex.cfloor_y * 64) % 64;
		pxto_win(x, S_HEIGHT - y, *((int *)mlx->tex[0] + 64 * v->tex.tex_y + v->tex.tex_x), mlx);
		pxto_win(x, y, *((int *)mlx->tex[0] + 64 * v->tex.tex_y + v->tex.tex_x), mlx);
		y++;
	}
}

void	fc_calc(t_trigger *t, t_p_coords *v)
{
	if (t->side == 0 && v->rayDir.X > 0)
	{
		v->tex.floor_x = v->map.x;
		v->tex.floor_y = v->map.y + v->tex.wall_x;
	}
	else if (t->side == 0 && v->rayDir.X < 0)
	{
		v->tex.floor_x = v->map.x + 1.0;
		v->tex.floor_y = v->map.y + v->tex.wall_x;
	}
	else if (t->side == 1 && v->rayDir.Y > 0)
	{
		v->tex.floor_x = v->map.x + v->tex.wall_x;
		v->tex.floor_y = v->map.y;
	}
	else
	{
		v->tex.floor_x = v->map.x + v->tex.wall_x;
		v->tex.floor_y = v->map.y + 1.0;
	}
}


void	drawSlide(int x, t_proj_ray *curr, t_trigger *t, t_p_coords *v, t_mlx *mlx)
{
	int i;
	int y;
	int y_end;

	i = S_HEIGHT - 1;
	y = curr->drawStart;
	y_end = curr->drawEnd;
	v->tex.start = y;
	v->tex.end = y_end;
	tex_calc(t, v);
	fc_calc(t, v);
while (y != y_end)
	{
		v->tex.d = y * 256 - S_HEIGHT * 128 + v->lineHeight * 128;
		v->tex.tex_y = ((v->tex.d * 64) / v->lineHeight) / 256;
		pxto_win(x, y, *((int *)mlx->tex[0] + 64 * v->tex.tex_y + v->tex.tex_x), mlx);
		y++;
	}
	floor_tex(x, v, mlx);
}

void	mapping(t_p_coords *v, int **map, t_proj_ray *curr, t_trigger *t)
{
	// int 		hit;
	// int		side;
//	t_dist 		d;
	// which square
	v->map.x = (int)v->pos.X;
	v->map.y = (int)v->pos.Y;
	v->d.deltaDist.X = ft_abs_val(1.0 / v->rayDir.X);
	v->d.deltaDist.Y = ft_abs_val(1.0 / v->rayDir.Y);
	// printf("ddistx %f, ddisty %f\n", d.deltaDist.X, d.deltaDist.Y);
	t->hit = 0;
	get_direction(v, &v->d);

	// do DDA
	do_DDA(v, &v->d, t, map);
	// get the perpendicular distance of the wall hit, use side to determinate w
	// wether x dist or y dist
	if (t->side == 0)
		v->d.perpWallDist = (v->map.x - v->pos.X + (1 - v->step.x) / 2) / v->rayDir.X;
	else
		v->d.perpWallDist = (v->map.y - v->pos.Y + (1 - v->step.y) / 2) / v->rayDir.Y;
	// height of the wall depends on distance and pixel height
	//  we calculate it here
	v->lineHeight = (int)(S_HEIGHT * 1.5 / v->d.perpWallDist);
	// we make a pixel range we have to draw in our stripe
	curr->drawStart = -v->lineHeight / 2 + S_HEIGHT / 2;
	if (curr->drawStart < 0)
		curr->drawStart = 0;
	curr->drawEnd = v->lineHeight / 2 + S_HEIGHT / 2;
	if (curr->drawEnd >= S_HEIGHT)
		curr->drawEnd = S_HEIGHT - 1;
}

void	get_direction(t_p_coords *v, t_dist *d)
{
	if (v->rayDir.X < 0)
	{
		// direction
		v->step.x = -1;
		// lenght of ray from current pos to side
		d->sideDist.X = (v->pos.X - v->map.x) * d->deltaDist.X;
	}
	else
	{
		v->step.x = 1;
		d->sideDist.X = (v->map.x + 1.0 - v->pos.X) * d->deltaDist.X; 
	}
	if (v->rayDir.Y < 0)
	{
		v->step.y = -1;
		d->sideDist.Y = (v->pos.Y - v->map.y) * d->deltaDist.Y;
	}
	else
	{
		v->step.y = 1;
		d->sideDist.Y = (v->map.y + 1.0  - v->pos.Y) * d->deltaDist.Y;
	}	
}

void	do_DDA(t_p_coords *v, t_dist *d, t_trigger *t, int **map)
{
	while (t->hit == 0)
	{
		// go next x or y
		if (d->sideDist.X < d->sideDist.Y)
		{
			d->sideDist.X += d->deltaDist.X;
			v->map.x += v->step.x;
			t->side = 0;
		}
		else
		{
			d->sideDist.Y += d->deltaDist.Y;
			v->map.y += v->step.y;
			t->side = 1;
		}
		// wall condition
		if (map[v->map.x][v->map.y] > 0)
			t->hit = 1; 
	}
}
int		main(void)
{
	t_mlx	mlx;
	t_p_coords v;

	mlx.v = &v;
	// int **true_map;
	init(&mlx, &v);

/*	int map[WIDTH][HEIGHT] = {
 {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};
*/


	int map[WIDTH][HEIGHT] = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

	mlx.map = give_map();
	for (int x = 0; x < WIDTH; x++)
		for (int y = 0; y < HEIGHT; y++)
			mlx.map[x][y] = map[x][y];
	
	cast_all_rays(&v, mlx.map, &mlx);

	// mlx_key_hook(mlx.win_ptr, deal_key, (void *)&mlx);
	// mlx_mouse_hook(mlx.win_ptr, do_mouse, (void *)&mlx);
	// mlx_hook(mlx.win_ptr, 6, 0, do_jul_mov, &mlx);
	mlx_key_hook(mlx.win_ptr, keys, &mlx.mlx_ptr);
	mlx_hook(mlx.win_ptr, 17, 0, redx, &mlx.mlx_ptr);
	mlx_hook(mlx.win_ptr, 2, 0, press, &mlx.mlx_ptr);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
