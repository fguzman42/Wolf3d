/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 13:47:44 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/05/25 03:28:42 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*map;
	size_t	i;
	size_t	j;

	j = ft_strlen((char *)s);
	i = 0;
	map = NULL;
	if (s && f)
	{
		if (!(map = (char *)malloc(sizeof(char) * (j + 1))))
			return (NULL);
		while (i < j)
		{
			map[i] = f(i, s[i]);
			i++;
		}
		map[i] = '\0';
	}
	return (map);
}
