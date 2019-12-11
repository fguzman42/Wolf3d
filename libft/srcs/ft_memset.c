/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 19:11:33 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/08/27 20:03:11 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int i;

	i = 0;
	while (i < len)
	{
		(*((unsigned char *)b + i)) = (unsigned char)c;
		i++;
	}
	return (b);
}
