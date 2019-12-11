/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 12:15:13 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/12/04 12:26:09 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

t_slide		*inter(t_slide *res, char *line)
{
	int			i;
	int			j;
	int			k;
	char		*tmp;

	k = 0;
	i = 0;
	res->xslide = (int *)malloc(sizeof(int) * (ft_countwords(line, '\t') + \
	ft_countwords(line, ' ') + 1));
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
	res->size = k;
	free(line);
	return (res);
}

t_slide		*list_slider(int fd, char *line)
{
	int			i;
	t_slide		*head;
	t_slide		*travel;
	t_slide		*current;

	i = -1;
	head = (t_slide *)malloc(sizeof(t_slide));
	current = (t_slide *)malloc(sizeof(t_slide));
	while (get_next_line(fd, &line) > 0)
	{
		if (++i == 0)
		{
			inter(head, line);
			head->next = NULL;
			travel = head;
		}
		else
		{
			inter(current, line);
			travel = node_add(travel, current->xslide, current->size);
		}
	}
	free(current);
	return (head);
}

t_grid		create_2d_array(t_slide *head, int n_elements)
{
	int		k;
	t_grid	grid;

	k = 0;
	grid.map = (int **)malloc(sizeof(int *) * (n_elements));
	grid.xsize = head->size;
	grid.ysize = n_elements;
	while (head != NULL)
	{
		grid.map[k] = head->xslide;
		k++;
		head = head->next;
	}
	return (grid);
}