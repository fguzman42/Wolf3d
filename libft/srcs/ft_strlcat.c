/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 19:44:28 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/05/23 20:40:10 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t			dlen;
	char			*tmp;
	size_t			i;
	size_t			slen;

	if (dstsize == 0)
		return (dstsize + ft_strlen(src));
	dlen = ft_strlen(dst);
	tmp = dst + dlen;
	i = 0;
	while (src[i] && (dlen + i < dstsize - 1))
	{
		tmp[i] = src[i];
		++i;
	}
	tmp[i] = '\0';
	slen = ft_strlen(src);
	if (dlen > dstsize)
		return (dstsize + slen);
	return (dlen + slen);
}
