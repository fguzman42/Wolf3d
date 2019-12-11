/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 13:47:44 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/05/23 20:59:12 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*res;
	unsigned int	i;

	i = 0;
	if (!(res = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	if (f != NULL && s != NULL)
	{
		while (s[i] != '\0')
		{
			res[i] = (char)(f(s[i]));
			i++;
		}
		res[i] = '\0';
	}
	return (res);
}
