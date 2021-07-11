/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:38:58 by kjaco             #+#    #+#             */
/*   Updated: 2020/11/21 19:33:08 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (src[i])
		i++;
	j = 0;
	k = 0;
	if (dstsize == 0)
		return (i);
	while (dst[j++])
		i++;
	if (dstsize < j--)
	{
		return (i - j + dstsize);
	}
	while (dstsize - j - 1 && src[k])
	{
		dst[j] = src[k];
		j++;
		k++;
	}
	dst[j] = 0;
	return (i);
}
