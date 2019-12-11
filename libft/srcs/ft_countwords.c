/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 21:23:15 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/05/23 21:23:48 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_countwords(char const *str, char c)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (str[i] == c)
		i++;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] != c)
			i++;
		while (str[i] != '\0' && str[i] == c)
			i++;
		n++;
	}
	return (n);
}
