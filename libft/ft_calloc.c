/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 22:09:59 by kjaco             #+#    #+#             */
/*   Updated: 2020/11/21 19:34:08 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*arr;

	i = 0;
	arr = malloc(count * size);
	if (arr == NULL)
		return (NULL);
	while (i != count * size)
	{
		arr[i] = 0;
		i++;
	}
	return (arr);
}
