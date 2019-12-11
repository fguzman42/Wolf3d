/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdmpnfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 11:05:30 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/09/24 11:06:43 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strdmpnfree(char *source, char *dst, int len, int start)
{
	int i;

	i = 0;
	while (len > 0)
	{
		dst[start] = source[i];
		start++;
		i++;
		len--;
	}
	free(source);
	return (start);
}
