/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:56:36 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/12/13 03:26:19 by fguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	init(t_mlx *mlx, t_p_coords *v, char *argv)
{
	v->pos.x = 22;
	v->pos.y = 12;
	v->dir.x = -1;
	v->dir.y = 0;
	v->plane.x = 0;
	v->plane.y = 0.66;
	v->time = 0;
	v->oldtime = 0;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, S_WIDTH, S_HEIGHT, "wolf3d");
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, S_WIDTH, S_HEIGHT);
	mlx->pixs = mlx_get_data_addr(mlx->img_ptr, &mlx->bpp,\
	&mlx->sline, &mlx->endian);
	mlx->tex = tex(mlx);
	if (ft_strcmp(argv, "mario") == 0)
		system("afplay -v 2 sounds/mario.mp3 &");
	else if (ft_strcmp(argv, "wolf") == 0)
		system("afplay -v 2 sounds/wolf.mp3 &");
	else
		system("afplay -v 2 sounds/default.mp3 &");
}

void	cast_all_rays(t_p_coords *v, int **map, t_mlx *mlx)
{
	double		camerax;
	t_proj_ray	curslide;
	t_trigger	t;

	mlx->x = 0;
	while (mlx->x < S_WIDTH)
	{
		camerax = 2 * mlx->x / (double)S_WIDTH - 1;
		v->raydir.x = v->dir.x + v->plane.x * camerax;
		v->raydir.y = v->dir.y + v->plane.y * camerax;
		mapping(v, map, &curslide, &t);
		mlx->t_index = mlx->map[v->map.x][v->map.y] % 10 - 1;
		drawslide(&curslide, &t, v, mlx);
		mlx->x++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}

void	tex_calc(t_trigger *t, t_p_coords *v)
{
	if (t->side == 0)
		v->tex.wall_x = v->pos.y + v->d.perpwalldist * v->raydir.y;
	else
		v->tex.wall_x = v->pos.x + v->d.perpwalldist * v->raydir.x;
	v->tex.wall_x -= floor((v->tex.wall_x));
	v->tex.tex_x = (int)(v->tex.wall_x * (double)(64));
	if (t->side == 0 && v->raydir.x > 0)
		v->tex.tex_x = 64 - v->tex.tex_x - 1;
	if (t->side == 1 && v->raydir.y < 0)
		v->tex.tex_x = 64 - v->tex.tex_x - 1;
}

void	floor_tex(t_p_coords *v, t_mlx *mlx)
{
	int y;

	v->tex.distwall = v->d.perpwalldist;
	v->tex.distplayer = 0.0;
	if (v->tex.end < 0)
		v->tex.end = S_HEIGHT;
	y = v->tex.end + 1;
	while (y < S_HEIGHT)
	{
		v->tex.currentdist = S_HEIGHT / (2.0 * y - S_HEIGHT);
		v->tex.weight = (v->tex.currentdist - v->tex.distplayer)
			/ (v->tex.distwall - v->tex.distplayer);
		v->tex.cfloor_x = v->tex.weight * v->tex.floor_x +
			(1.0 - v->tex.weight) * v->pos.x;
		v->tex.cfloor_y = v->tex.weight * v->tex.floor_y +
			(1.0 - v->tex.weight) * v->pos.y;
		v->tex.tex_x = (int)(v->tex.cfloor_x * 64) % 64;
		v->tex.tex_y = (int)(v->tex.cfloor_y * 64) % 64;
		pxto_win(mlx->x, S_HEIGHT - y, *((int *)mlx->tex[1] +
			64 * v->tex.tex_y + v->tex.tex_x), mlx);
		pxto_win(mlx->x, y, *((int *)mlx->tex[2] +
			64 * v->tex.tex_y + v->tex.tex_x), mlx);
		y++;
	}
}

void	fc_calc(t_trigger *t, t_p_coords *v)
{
	if (t->side == 0 && v->raydir.x > 0)
	{
		v->tex.floor_x = v->map.x;
		v->tex.floor_y = v->map.y + v->tex.wall_x;
	}
	else if (t->side == 0 && v->raydir.x < 0)
	{
		v->tex.floor_x = v->map.x + 1.0;
		v->tex.floor_y = v->map.y + v->tex.wall_x;
	}
	else if (t->side == 1 && v->raydir.y > 0)
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

void	drawslide(t_proj_ray *curr, t_trigger *t, t_p_coords *v, t_mlx *mlx)
{
	int i;
	int y;
	int y_end;

	i = S_HEIGHT - 1;
	y = curr->drawstart;
	y_end = curr->drawend;
	v->tex.end = y_end;
	tex_calc(t, v);
	fc_calc(t, v);
	while (y != y_end)
	{
		v->tex.d = y * 256 - S_HEIGHT * 128 + v->lineheight * 128;
		v->tex.tex_y = ((v->tex.d * 64) / v->lineheight) / 256;
		pxto_win(mlx->x, y, *((int *)mlx->tex[mlx->t_index] +
			64 * v->tex.tex_y + v->tex.tex_x), mlx);
		y++;
	}
	floor_tex(v, mlx);
}

void	mapping(t_p_coords *v, int **map, t_proj_ray *curr, t_trigger *t)
{
	v->map.x = (int)v->pos.x;
	v->map.y = (int)v->pos.y;
	v->d.deltadist.x = ft_abs_val(1.0 / v->raydir.x);
	v->d.deltadist.y = ft_abs_val(1.0 / v->raydir.y);
	t->hit = 0;
	get_direction(v, &v->d);
	do_dda(v, &v->d, t, map);
	if (t->side == 0)
		v->d.perpwalldist = (v->map.x - v->pos.x +
		(1 - v->step.x) / 2) / v->raydir.x;
	else
		v->d.perpwalldist = (v->map.y - v->pos.y +
		(1 - v->step.y) / 2) / v->raydir.y;
	if (v->d.perpwalldist == 0)
		v->d.perpwalldist = 1;
	v->lineheight = (int)(S_HEIGHT * 1.5 / v->d.perpwalldist);
	curr->drawstart = -v->lineheight / 2 + S_HEIGHT / 2;
	if (curr->drawstart < 0)
		curr->drawstart = 0;
	curr->drawend = v->lineheight / 2 + S_HEIGHT / 2;
	if (curr->drawend >= S_HEIGHT)
		curr->drawend = S_HEIGHT - 1;
}

void	get_direction(t_p_coords *v, t_dist *d)
{
	if (v->raydir.x < 0)
	{
		v->step.x = -1;
		d->sidedist.x = (v->pos.x - v->map.x) * d->deltadist.x;
	}
	else
	{
		v->step.x = 1;
		d->sidedist.x = (v->map.x + 1.0 - v->pos.x) * d->deltadist.x;
	}
	if (v->raydir.y < 0)
	{
		v->step.y = -1;
		d->sidedist.y = (v->pos.y - v->map.y) * d->deltadist.y;
	}
	else
	{
		v->step.y = 1;
		d->sidedist.y = (v->map.y + 1.0 - v->pos.y) * d->deltadist.y;
	}
}

void	do_dda(t_p_coords *v, t_dist *d, t_trigger *t, int **map)
{
	while (t->hit == 0)
	{
		if (d->sidedist.x < d->sidedist.y)
		{
			d->sidedist.x += d->deltadist.x;
			v->map.x += v->step.x;
			t->side = 0;
		}
		else
		{
			d->sidedist.y += d->deltadist.y;
			v->map.y += v->step.y;
			t->side = 1;
		}
		if (map[v->map.x][v->map.y] > 0)
			t->hit = 1;
	}
}

int		main(int argc, char **argv)
{
	t_mlx		mlx;
	t_p_coords	v;
	t_slide		*head;
	t_grid		grid;

	mlx.line = NULL;
	mlx.v = &v;
	mlx.fd = open(argv[1], O_RDONLY);
	if (mlx.fd < 0 || argc != 2)
		return (err_ret("Usage : ./fdf <path to map>"));
	if (check_file(mlx.fd, &grid) == 1)
		return (err_ret("shitty map man"));
	init(&mlx, &v, argv[1]);
	head = list_scroller(argv[1], mlx.line, &grid.ysize);
	create_2d_array(head, grid.ysize, &grid);
	if (get_spawn(&v, &grid) == 0)
		err_ret("no spawn!");
	mlx.map = grid.map;
	cast_all_rays(&v, mlx.map, &mlx);
	mlx_key_hook(mlx.win_ptr, keys, &mlx.mlx_ptr);
	mlx_hook(mlx.win_ptr, 17, 0, redx, &mlx.mlx_ptr);
	mlx_hook(mlx.win_ptr, 2, 0, press, &mlx.mlx_ptr);
	free_list(head);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
