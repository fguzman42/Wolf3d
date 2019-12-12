/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:57:00 by fguzman           #+#    #+#             */
/*   Updated: 2019/12/11 17:35:50 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	move_player(t_mlx *mlx, t_p_coords *v, double speed, int mode)
{
	if (mode == FORWARD)
	{
		v->pos.X += v->dir.X * speed;
		v->pos.Y += v->dir.Y * speed;
		cast_all_rays(v, mlx->map, mlx);
	}
	if (mode == BACKWARD)
	{
		v->pos.X -= v->dir.X * speed;
		v->pos.Y -= v->dir.Y * speed;
		cast_all_rays(v, mlx->map, mlx);
	}
	if (mode == LEFT)
	{
		v->pos.X -= v->plane.X * speed;
		v->pos.Y -= v->plane.Y * speed;
		cast_all_rays(v, mlx->map, mlx);
	}
	if (mode == RIGHT)
	{
		v->pos.X += v->plane.X * speed;
		v->pos.Y += v->plane.Y * speed;
		cast_all_rays(v, mlx->map, mlx);
	}
}

void	fblr(t_mlx *mlx, t_p_coords *v, int **map, int key)
{
	double speed;

	speed = 0.5;
	if (0 >= (map[(int)(v->pos.X + v->plane.X * speed)][(int)(v->pos.Y)]) &&
	0 >= (map[(int)(v->pos.X)][(int)(v->pos.Y + v->plane.Y * speed)]) &&
	key == 124)
		move_player(mlx, v, speed, RIGHT);
	if (0 >= (map[(int)(v->pos.X - v->plane.X * speed)][(int)(v->pos.Y)]) &&
	0 >= (map[(int)(v->pos.X)][(int)(v->pos.Y - v->plane.Y * speed)]) &&
	key == 123)
		move_player(mlx, v, speed, LEFT);
	if (0 >= (map[(int)(v->pos.X + v->dir.X * speed)][(int)(v->pos.Y)]) &&
	0 >= (map[(int)(v->pos.X)][(int)(v->pos.Y + v->dir.Y * speed)]) &&
	key == 126)
		move_player(mlx, mlx->v, speed, FORWARD);
	if (0 >= (map[(int)(v->pos.X - v->dir.X * speed)][(int)(v->pos.Y)]) &&
	0 >= (map[(int)(v->pos.X)][(int)(v->pos.Y - v->dir.Y * speed)]) &&
	key == 125)
		move_player(mlx, mlx->v, speed, BACKWARD);
}

int		redx(t_mlx *mlx)
{
	int i;

	i = 53;
	keys(i, mlx);
	return (0);
}

void	movecam(t_mlx *mlx, int key)
{
	double olddirx;
	double oldplanex;
	double speed;

	speed = 0.1;
	olddirx = mlx->v->dir.X;
	oldplanex = mlx->v->plane.X;
	if (key == 2)
	{
		speed = -0.05;
		mlx->v->dir.X = mlx->v->dir.X * cos(speed) - mlx->v->dir.Y * sin(speed);
		mlx->v->dir.Y = olddirx * sin(speed) + mlx->v->dir.Y * cos(speed);
		mlx->v->plane.X = mlx->v->plane.X * cos(speed) - mlx->v->plane.Y * sin(speed);
		mlx->v->plane.Y = oldplanex * sin(speed) + mlx->v->plane.Y * cos(speed);
		cast_all_rays(mlx->v, mlx->map, mlx);
	}
	if (key == 0)
	{
		mlx->v->dir.X = mlx->v->dir.X * cos(speed) - mlx->v->dir.Y * sin(speed);
		mlx->v->dir.Y = olddirx * sin(speed) + mlx->v->dir.Y * cos(speed);
		mlx->v->plane.X = mlx->v->plane.X * cos(speed) - mlx->v->plane.Y * sin(speed);
		mlx->v->plane.Y = oldplanex * sin(speed) + mlx->v->plane.Y * cos(speed);
		cast_all_rays(mlx->v, mlx->map, mlx);
	}
}

int		press(int key, t_mlx *mlx)
{
	keys(key, mlx);
	return (0); 
}

int		release(int key, t_mlx *mlx)
{
	keys(key, mlx);
	return (0);
}

int		keys(int key, t_mlx *mlx)
{
	if (key == 53)
	{
		system("pkill afplay");
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		exit(0);
	}
	if (key >= 123 && key <= 126)
		fblr(mlx, mlx->v, mlx->map, key);
	if (key == 0 || key == 2)
		movecam(mlx, key);
	return (0);
}
