/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 19:39:43 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/09 14:40:42 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*d)(void *))
{
	t_list	*rez;
	t_list	*tmp;

	rez = NULL;
	if (lst == NULL)
		return (NULL);
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (tmp == NULL)
		{
			ft_lstclear(&rez, d);
			return (NULL);
		}
		ft_lstadd_back(&rez, tmp);
		lst = lst->next;
	}
	return (rez);
}
