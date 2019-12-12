/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 22:47:55 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/12/04 11:47:31 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

char		**tex(t_mlx *mlx)
{
	int x;
	int y;

	x = 64;
	y = 64;
	mlx->tex = (char **)malloc(sizeof(char *) * 10);
	mlx->tex[0] = mlx_get_data_addr((mlx_xpm_file_to_image(mlx->mlx_ptr, "./pics/mariowall.XPM", &x, &y)), &mlx->bpp,\
	&mlx->sline, &mlx->endian);	
	mlx->tex[1] = mlx_get_data_addr((mlx_xpm_file_to_image(mlx->mlx_ptr, "./pics/marioceiling.xpm", &x, &y)), &mlx->bpp,\
	&mlx->sline, &mlx->endian);
	mlx->tex[2] = mlx_get_data_addr((mlx_xpm_file_to_image(mlx->mlx_ptr, "./pics/marioground.xpm", &x, &y)), &mlx->bpp,\
	&mlx->sline, &mlx->endian);
	mlx->tex[3] = mlx_get_data_addr((mlx_xpm_file_to_image(mlx->mlx_ptr, "./pics/mariohill.XPM", &x, &y)), &mlx->bpp,\
	&mlx->sline, &mlx->endian);
	mlx->tex[4] = mlx_get_data_addr((mlx_xpm_file_to_image(mlx->mlx_ptr, "./pics/goal.XPM", &x, &y)), &mlx->bpp,\
	&mlx->sline, &mlx->endian);
	mlx->tex[5] = mlx_get_data_addr((mlx_xpm_file_to_image(mlx->mlx_ptr, "./pics/skulls.xpm", &x, &y)), &mlx->bpp,\
	&mlx->sline, &mlx->endian);
	mlx->tex[6] = mlx_get_data_addr((mlx_xpm_file_to_image(mlx->mlx_ptr, "./pics/barrel.xpm", &x, &y)), &mlx->bpp,\
	&mlx->sline, &mlx->endian);
	mlx->tex[7] = mlx_get_data_addr((mlx_xpm_file_to_image(mlx->mlx_ptr, "./pics/skulls.xpm", &x, &y)), &mlx->bpp,\
	&mlx->sline, &mlx->endian);
	mlx->tex[8] = mlx_get_data_addr((mlx_xpm_file_to_image(mlx->mlx_ptr, "./pics/barrel.xpm", &x, &y)), &mlx->bpp,\
	&mlx->sline, &mlx->endian);
/*	tex[9] = 0xD3ECF8;
	tex[10] = 0xF1E9BF;
	tex[11] = 0xF8C95F;
	tex[12] = 0xFFAA00;
	tex[13] = 0xCC8000;
	tex[14] = 0x995700;
	tex[15] = 0x6A3403;*/
	return (mlx->tex);
}


void	pxto_win(int x, int y, int color, t_mlx *mlx)
{
	int index;

	color = mlx_get_color_value(mlx->mlx_ptr, color);
	index = (4 * S_WIDTH * y + x * 4);
	ft_memcpy(mlx->pixs + index, &color, sizeof(int));
}

int	**give_map()
{
	int		**map;
	int		i;

	i = 0;
	map = (int **)malloc(sizeof(int *) * WIDTH);
	while(i < HEIGHT)
	{
		map[i] = (int *)malloc(sizeof(int) * HEIGHT);
		i++;
	}
	return(map);
}