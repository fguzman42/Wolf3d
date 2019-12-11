/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 20:30:55 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/05/24 00:12:27 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**strs;

	i = 0;
	j = 0;
	k = 0;
	MCK((strs = (char **)malloc(sizeof(char *)
	* ((ft_countwords(s, c)) + 1))), NULL);
	while (s[i] != '\0' && s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		j = i;
		while (s[i] != '\0' && s[i] != c)
			i++;
		strs[k] = ft_strsub(s, j, (i - j));
		k++;
		while (s[i] != '\0' && s[i] == c)
			i++;
	}
	strs[k] = NULL;
	return (strs);
}
