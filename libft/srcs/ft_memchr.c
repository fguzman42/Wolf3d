/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 14:38:01 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/05/18 11:35:38 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*res;

	res = (unsigned char *)s;
	while (n--)
	{
		if (*res == (unsigned char)c)
			return (res);
		res++;
	}
	return (NULL);
}
