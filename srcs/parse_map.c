/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 12:15:13 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/12/13 17:09:32 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

t_slide	*inter(char *line)
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

t_slide	*list_scroller(char *path, char *line, int *ysize)
{
	int		i;
	t_slide	*head;
	int		fd;

	fd = open(path, O_RDONLY);
	head = NULL;
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
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
	return (head);
}

t_slide	*node_add(t_slide *anywhere, char *line)
{
	t_slide *new;

	new = inter(line);
	while (anywhere->next != NULL)
		anywhere = anywhere->next;
	anywhere->next = new;
	new->next = NULL;
	return (new);
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
			return (0);
		i++;
		j = -1;
		while (line[++j] != '\0')
			if ((line[j] < 48 || line[j] > 57) && line[j]\
			!= ' ' && line[j] != '\t' && line[j] != '-')
				return (0);
		free(line);
	}
	close(fd);
	grid->xsize = len;
	return (i);
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
