/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:15:20 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/09/24 11:20:12 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strsubcpy(char *source, char *dst, int len, int start)
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
	return (start);
}
