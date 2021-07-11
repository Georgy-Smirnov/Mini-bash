/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 19:10:49 by kjaco             #+#    #+#             */
/*   Updated: 2020/11/21 19:32:54 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	int		j;

	i = 0;
	if (!dst)
		return (0);
	while (src[i])
		i++;
	j = 0;
	if (dstsize == 0)
		return (i);
	while (dstsize - 1 && src[j])
	{
		dst[j] = src[j];
		j++;
		dstsize--;
	}
	dst[j] = 0;
	return (i);
}
