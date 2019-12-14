/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:47:30 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/12/13 19:56:29 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	create_net(int k, t_grid *grid)
{
	int x;

	x = -1;
	while (++x < grid->xsize + 2)
	{
		grid->map[k][x] = 1;
		grid->map[0][x] = 1;
	}
	x = -1;
	while (++x < grid->ysize + 2)
	{
		grid->map[x][0] = 1;
		grid->map[x][grid->xsize + 1] = 1;
	}
}

int		get_spawn(t_p_coords *v, t_grid *g)
{
	int		hit;
	t_point n;

	n.x = 0;
	hit = 0;
	g->xsize += 2;
	g->ysize += 2;
	while (n.x < g->xsize)
	{
		n.y = 0;
		while (n.y < g->ysize)
		{
			if (g->map[n.y][n.x] == -1 || (hit == 0 && g->map[n.y][n.x] == 0))
			{
				v->pos.x = n.x;
				v->pos.x = n.y;
				hit++;
				if (g->map[n.y][n.x] == -1)
					return (1);
			}
			n.y++;
		}
		n.x++;
	}
	return (hit);
}

void	create_2d_array(t_slide *head, int n_elements, t_grid *grid)
{
	int		k;

	k = 1;
	grid->map = (int **)malloc(sizeof(int *) * (n_elements + 2));
	grid->xsize = head->size;
	grid->ysize = n_elements;
	grid->map[0] = (int *)malloc(sizeof(int) * head->size + 2);
	while (head != NULL)
	{
		grid->map[k] = head->xslide;
		k++;
		head = head->next;
	}
	grid->map[k] = (int *)malloc(sizeof(int) * grid->xsize + 1);
	create_net(k, grid);
}
