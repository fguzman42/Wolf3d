/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 19:13:02 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/05/25 05:29:56 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int		i;

	if (len == 0 || src == NULL)
		return (dst);
	if ((long int)dst > (long int)src)
	{
		i = (int)len;
		while (--i > -1)
			((char *)dst)[i] = ((char *)src)[i];
	}
	else
	{
		i = -1;
		while (++i < (int)len)
			((char *)dst)[i] = ((char *)src)[i];
	}
	return (dst);
}
