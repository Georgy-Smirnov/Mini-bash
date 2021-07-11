/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 19:06:27 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/09 14:43:36 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	int	i;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n != 0)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
		n--;
	}
	return (dst);
}
