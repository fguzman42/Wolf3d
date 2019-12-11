/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 14:44:42 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/05/24 15:10:20 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *lem))
{
	t_list	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		f(lst);
		lst = tmp;
	}
}
