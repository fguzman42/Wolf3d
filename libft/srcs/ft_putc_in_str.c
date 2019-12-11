/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putc_in_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 11:36:59 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/09/14 14:01:47 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putc_in_str(char *src, char c, int len, int start)
{
	while (len)
	{
		src[start] = c;
		len--;
		start++;
	}
	return (start);
}
