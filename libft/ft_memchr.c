/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 19:53:44 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/09 14:41:12 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *s, int c, size_t n)
{
	unsigned char	*rez;
	unsigned char	sym;

	rez = (unsigned char *)s;
	sym = (unsigned char)c;
	while (n)
	{
		if (*rez == sym)
			return (rez);
		rez++;
		n--;
	}
	return (NULL);
}
