/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 17:36:11 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/12/11 17:40:03 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

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