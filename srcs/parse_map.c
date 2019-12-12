/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 12:15:13 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/12/11 00:22:41 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

t_slide		*inter(char *line)
{
	int			i;
	int			j;
	int			k;
	char		*tmp;
	t_slide		*res;

	res = (t_slide *)malloc(sizeof(t_slide));
	k = 1;
	i = 0;
	res->xslide = (int *)malloc(sizeof(int) * ft_countwords(line, ' ') + 2);
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'))
			i++;
		j = i;
		while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t')
			i++;
		tmp = ft_strsub(line, j, i - j);
		res->xslide[k] = atoi(tmp);
		free(tmp);
		k++;
	}
	res->size = k - 1;
	return (res);
}

t_slide		*list_scroller(char *path, char *line, int *ysize)
{
	
	int		i;
	t_slide	*head;
	int		fd;
	
	fd = open(path, O_RDONLY);
	// printf("funct\n");
	head = NULL;
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		// printf("loop\n");
		if (!head)
			{
				head = inter(line);
				head->next = NULL;
				i++;
			}
		else
			{
				node_add(head, line);
				i++;
			}
		free(line);
	}
	*ysize = i;
	return(head);
}

t_slide		*node_add(t_slide *anywhere, char *line)
{
	t_slide *new;

	new = inter(line);
	while (anywhere->next != NULL)
		anywhere = anywhere->next;
	anywhere->next = new;
	new->next = NULL;
	return (new);
}

// t_slide		*list_slider(int fd, char *line)
// {
// 	int			i;
// 	t_slide		*head;
// 	t_slide		*travel;
// 	t_slide		*current;

// 	i = -1;
// 	head = (t_slide *)malloc(sizeof(t_slide));
// 	current = (t_slide *)malloc(sizeof(t_slide));
// 	while (get_next_line(fd, &line) > 0)
// 	{
// 		if (++i == 0)
// 		{
// 			inter(head, line);
// 			head->next = NULL;
// 			travel = head;
// 		}
// 		else
// 		{
// 			inter(current, line);
// 			travel = node_add(travel, current->xslide, current->size);
// 		}
// 	}
// 	free(current);
// 	return (head);
// }

void		create_2d_array(t_slide *head, int n_elements, t_grid *grid)
{
	int		k;
	int		x;
	int		y;

	y = 0;
	x = -1;
	k = 1;
	printf(" - %d\n", head->size);
	grid->map = (int **)malloc(sizeof(int *) * (n_elements + 2));
	grid->xsize = head->size;
	grid->ysize = n_elements;
	grid->map[0] = (int *)malloc(sizeof(int) * head->size + 2);
	while (head != NULL)
	{
		grid->map[k] = head->xslide;
		printf("adding slides%d\n", n_elements);
		k++;
		head = head->next;
	}
	grid->map[k] = (int *)malloc(sizeof(int) * grid->xsize + 1);
	x = -1;
	printf("xsize is : %d, ysize is : %d\n", grid->xsize, grid->ysize);
	while(++x < grid->xsize + 2)
	{
		grid->map[k][x] = 1;
		// grid.map[x][0] = 1;
		grid->map[0][x] = 1;
		// grid.map[x][grid.xsize - 1] = 1;		
	}
	while(y < grid->ysize + 2)
	{
		grid->map[y][0] = 1;
		grid->map[y][grid->xsize + 1] = 1;
		y++;
	}
	printf("here?\n");
	// return(grid->map);
}

int		check_file(int fd, t_grid *grid)
{
	int		i;
	int		len;
	char	*line;
	int		j;

	line = NULL;
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (i == 0)
			len = ft_countwords(line, ' ') + ft_countwords(line, '\t');
		else if (ft_countwords(line, ' ') + ft_countwords(line, '\t') != len)
			return (1);
		i++;
		j = -1;
		while (line[++j] != '\0')
			if ((line[j] < 48 || line[j] > 57) && line[j]\
			!= ' ' && line[j] != '\t' && line[j] != '-')
				return (1);
		free(line);
	}
	close(fd);
	grid->xsize = len;
	if (len == 0)
		return(1);
	return (0);
}



void	free_list(t_slide *head)
{
	if (head == NULL)
	return ;
	else
	{
		free_list(head->next);
		free(head);
	}
}

int		get_spawn(t_p_coords *v, t_grid *grid)
{
	int hit;
	int x;
	int y;
	
	x = 0;
	y = 0;
	hit = 0;
	grid->xsize += 2;
	grid->ysize += 2;
	while(x < grid->xsize)
	{
		y = 0;
		while(y < grid->ysize)
		{
			if (hit == 0 && grid->map[y][x] == 0)
			{
				hit++;
				v->pos.X = x;
				v->pos.Y = y;
			}
			if (grid->map[y][x] == -1)
			{
				v->pos.X = y;
				v->pos.Y = x;
				return(1);
			}
			y++;
		}
		x++;
	}
	return(hit);
}