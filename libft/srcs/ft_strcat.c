/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 20:35:53 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/05/23 21:02:17 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int i;
	int aplen;

	aplen = ft_strlen(s1);
	i = 0;
	while (s2[i] != '\0')
	{
		s1[aplen + i] = s2[i];
		i++;
	}
	s1[aplen + i] = '\0';
	return (s1);
}
