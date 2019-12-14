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

void	movecam(t_mlx *mlx, int key, t_p_coords *v)
{
	double olddirx;
	double oldplanex;
	double speed;

	speed = 0.1;
	olddirx = v->dir.x;
	oldplanex = v->plane.x;
	if (key == 2)
	{
		speed = -0.05;
		v->dir.x = v->dir.x * cos(speed) - v->dir.y * sin(speed);
		v->dir.y = olddirx * sin(speed) + v->dir.y * cos(speed);
		v->plane.x = v->plane.x * cos(speed) - v->plane.y * sin(speed);
		v->plane.y = oldplanex * sin(speed) + v->plane.y * cos(speed);
		cast_all_rays(v, mlx->map, mlx);
	}
	if (key == 0)
	{
		v->dir.x = v->dir.x * cos(speed) - v->dir.y * sin(speed);
		v->dir.y = olddirx * sin(speed) + v->dir.y * cos(speed);
		v->plane.x = v->plane.x * cos(speed) - v->plane.y * sin(speed);
		v->plane.y = oldplanex * sin(speed) + v->plane.y * cos(speed);
		cast_all_rays(v, mlx->map, mlx);
	}
}

void	move_player(t_mlx *mlx, t_p_coords *v, double speed, int mode)
{
	if (mode == FORWARD)
	{
		v->pos.x += v->dir.x * speed;
		v->pos.y += v->dir.y * speed;
		cast_all_rays(v, mlx->map, mlx);
	}
	if (mode == BACKWARD)
	{
		v->pos.x -= v->dir.x * speed;
		v->pos.y -= v->dir.y * speed;
		cast_all_rays(v, mlx->map, mlx);
	}
	if (mode == LEFT)
	{
		v->pos.x -= v->plane.x * speed;
		v->pos.y -= v->plane.y * speed;
		cast_all_rays(v, mlx->map, mlx);
	}
	if (mode == RIGHT)
	{
		v->pos.x += v->plane.x * speed;
		v->pos.y += v->plane.y * speed;
		cast_all_rays(v, mlx->map, mlx);
	}
}
