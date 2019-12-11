/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 11:32:32 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/05/25 02:55:44 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*link;
	int		i;

	if ((link = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (link == NULL)
		return (NULL);
	link->next = NULL;
	if (content == NULL)
	{
		link->content = NULL;
		link->content_size = 0;
	}
	else
	{
		link->content = malloc(content_size + 1);
		if (link->content == NULL)
			return (NULL);
		link->content_size = content_size;
		i = -1;
		while (++i < (int)content_size)
			((char *)(link->content))[i] = ((char *)content)[i];
	}
	return (link);
}
