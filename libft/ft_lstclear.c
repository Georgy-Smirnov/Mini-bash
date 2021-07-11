/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 19:18:23 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/09 14:40:17 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lst1;
	t_list	*tmp;

	lst1 = *lst;
	while (lst1)
	{
		tmp = lst1->next;
		ft_lstdelone(lst1, del);
		lst1 = tmp;
	}
	*lst = NULL;
}
