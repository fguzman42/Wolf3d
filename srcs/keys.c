/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:57:00 by fguzman           #+#    #+#             */
/*   Updated: 2019/12/13 19:49:05 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	fblr(t_mlx *mlx, t_p_coords *v, int **map, int key)
{
	double speed;

	speed = 0.5;
	if (key == 124
	&& 0 >= (map[(int)(v->pos.x + v->plane.x * speed)][(int)(v->pos.y)])
	&& 0 >= (map[(int)(v->pos.x)][(int)(v->pos.y + v->plane.y * speed)]))
		move_player(mlx, v, speed, RIGHT);
	if (key == 123
	&& 0 >= (map[(int)(v->pos.x - v->plane.x * speed)][(int)(v->pos.y)])
	&& 0 >= (map[(int)(v->pos.x)][(int)(v->pos.y - v->plane.y * speed)]))
		move_player(mlx, v, speed, LEFT);
	if (key == 126
	&& 0 >= (map[(int)(v->pos.x + v->dir.x * speed)][(int)(v->pos.y)])
	&& 0 >= (map[(int)(v->pos.x)][(int)(v->pos.y + v->dir.y * speed)]))
		move_player(mlx, v, speed, FORWARD);
	if (key == 125
	&& 0 >= (map[(int)(v->pos.x - v->dir.x * speed)][(int)(v->pos.y)])
	&& 0 >= (map[(int)(v->pos.x)][(int)(v->pos.y - v->dir.y * speed)]))
		move_player(mlx, v, speed, BACKWARD);
	if (key == 126
	&& (map[(int)(v->pos.x + v->dir.x * speed)][(int)(v->pos.y)] == 5
	|| map[(int)(v->pos.x)][(int)(v->pos.y + v->dir.y * speed)] == 5))
		toggle_goal_sound();
}

int		redx(t_mlx *mlx)
{
	int i;

	i = 53;
	keys(i, mlx);
	return (0);
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
		movecam(mlx, key, mlx->v);
	return (0);
}
