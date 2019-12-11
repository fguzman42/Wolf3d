/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:47:31 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/05/18 12:39:13 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	unsigned int i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		if (src[i] == '\0')
			while (i < len)
			{
				dst[i] = '\0';
				i++;
			}
		i++;
	}
	return (dst);
}
