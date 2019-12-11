/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 17:20:44 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/07/07 00:46:08 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		clear_buffer(int fd, char **line, char **fds)
{
	*line = ft_strdup(fds[fd]);
	ft_strdel(&fds[fd]);
	return (1);
}

int		newline_buffer(int fd, char **line, char **fds)
{
	int		i;
	char	*dump;

	i = 0;
	while (fds[fd][i] != '\n')
		i++;
	*line = ft_strsub(fds[fd], 0, i);
	dump = ft_strdup(fds[fd] + (i + 1));
	free(fds[fd]);
	fds[fd] = dump;
	if (ft_strlen(fds[fd]) < 1)
		ft_strdel(&fds[fd]);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char *fds[MAX_FD];
	int			read_ret;
	char		buffer[BUFF_SIZE + 1];
	char		*dump;

	while ((read_ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[read_ret] = '\0';
		if (fds[fd] == NULL)
			fds[fd] = ft_strnew(1);
		dump = ft_strjoin(fds[fd], buffer);
		free(fds[fd]);
		fds[fd] = dump;
		if (ft_strchr(fds[fd], '\n') != NULL)
			return (newline_buffer(fd, line, fds));
	}
	if (read_ret < 0 || BUFF_SIZE <= 0 || !line || fd < 0)
		return (-1);
	if ((fds[fd] == NULL || fds[fd][0] == '\0') && read_ret == 0)
		return (0);
	if (ft_strchr(fds[fd], '\n') != NULL)
		return (newline_buffer(fd, line, fds));
	return (clear_buffer(fd, line, fds));
}
