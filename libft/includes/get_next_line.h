/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 16:02:21 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/07/10 22:08:45 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# define BUFF_SIZE 10
# define MAX_FD 5000

int		get_next_line(int fd, char **line);
int		clear_buffer(int fd, char **line, char **fds);
int		newline_buffer(int fd, char **line, char **fds);
#endif
