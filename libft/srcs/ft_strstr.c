/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 17:49:40 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/05/20 13:50:53 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	int		nlen;

	nlen = ft_strlen(needle);
	i = 0;
	j = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		while (haystack[j + i] == needle[j] && j < nlen)
			j++;
		if (needle[j] == '\0')
			return ((char *)(haystack + i));
		j = 0;
		i++;
	}
	return (NULL);
}
