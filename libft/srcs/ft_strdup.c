/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:46:06 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/09/24 11:06:04 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_strdup(const char *s1)
{
	char	*str;

	if (!(str = (char*)malloc(sizeof(*str) * (1 + ft_strlen(s1)))))
		return (NULL);
	ft_strcpy(str, s1);
	return (str);
}
