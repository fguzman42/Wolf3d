/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:57:00 by fguzman           #+#    #+#             */
/*   Updated: 2019/12/04 12:13:45 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void fblr(t_mlx *mlx, int key)
{
    double speed;

    speed = 0.5;
    if (!(mlx->map[(int)(mlx->v->pos.X + mlx->v->plane.X * speed)][(int)(mlx->v->pos.Y)]) &&
        !(mlx->map[(int)(mlx->v->pos.X)][(int)(mlx->v->pos.Y + mlx->v->plane.Y * speed)]) && key == 124)
    {
        mlx->v->pos.X += mlx->v->plane.X * speed;
        mlx->v->pos.Y += mlx->v->plane.Y * speed;
        cast_all_rays(mlx->v, mlx->map, mlx);
    }
   if (!(mlx->map[(int)(mlx->v->pos.X - mlx->v->plane.X * speed)][(int)(mlx->v->pos.Y)]) &&
        !(mlx->map[(int)(mlx->v->pos.X)][(int)(mlx->v->pos.Y - mlx->v->plane.Y * speed)]) && key == 123)
    {
        mlx->v->pos.X -= mlx->v->plane.X * speed;
        mlx->v->pos.Y -= mlx->v->plane.Y * speed;
        cast_all_rays(mlx->v, mlx->map, mlx);
    }
    if (!(mlx->map[(int)(mlx->v->pos.X + mlx->v->dir.X * speed)][(int)(mlx->v->pos.Y)]) &&
        !(mlx->map[(int)(mlx->v->pos.X)][(int)(mlx->v->pos.Y + mlx->v->dir.Y * speed)]) && key == 126)
    {
        mlx->v->pos.X += mlx->v->dir.X * speed;
        mlx->v->pos.Y += mlx->v->dir.Y * speed;
        cast_all_rays(mlx->v, mlx->map, mlx);
    }
    if (!(mlx->map[(int)(mlx->v->pos.X - mlx->v->dir.X * speed)][(int)(mlx->v->pos.Y)]) &&
        !(mlx->map[(int)(mlx->v->pos.X)][(int)(mlx->v->pos.Y - mlx->v->dir.Y * speed)]) && key == 125)
    {
        mlx->v->pos.X -= mlx->v->dir.X * speed;
        mlx->v->pos.Y -= mlx->v->dir.Y * speed;
        cast_all_rays(mlx->v, mlx->map, mlx);
    }
}

int redx(t_mlx *mlx)
{
    int i;
    i = 53;
    keys(i, mlx);
    return (0);
}

void movecam(t_mlx *mlx, int key)
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

int press(int key, t_mlx *mlx)
{
    keys(key, mlx);
    return (0); 
}

int release(int key, t_mlx *mlx)
{
    keys(key, mlx);
    return (0);
}

int keys(int key, t_mlx *mlx)
{
  //  printf("%d", key);
    if (key == 53)
    {
        mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
        exit(0);
    }
    if (key >= 123 && key <= 126)
        fblr(mlx, key);
    if (key == 0 || key == 2)
        movecam(mlx, key);
    return (0);
}