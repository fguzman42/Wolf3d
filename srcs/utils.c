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

int		*colors(void)
{
	int *colors;

	colors = (int *)malloc(sizeof(int) * 16);
	colors[0] = 0xFF0000;
	colors[1] = 0x00FF00;
	colors[2] = 0x0000FF;
	colors[3] = 0x00FF0B;
	colors[4] = 0xFFFF00;
	colors[5] = 0x0C2C8A;
	colors[6] = 0x1852B1;
	colors[7] = 0x397DD1;
	colors[8] = 0x86B5E5;
	colors[9] = 0xD3ECF8;
	colors[10] = 0xF1E9BF;
	colors[11] = 0xF8C95F;
	colors[12] = 0xFFAA00;
	colors[13] = 0xCC8000;
	colors[14] = 0x995700;
	colors[15] = 0x6A3403;
	return (colors);
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