/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 21:08:21 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/09 14:37:19 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *hay, char *nee, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	if (nee[i] == 0)
		return (hay);
	while (hay[i] && (int)len - ft_strlen(nee) + 1 > 0)
	{
		k = i;
		while (nee[j])
		{
			if (hay[i] != nee[j])
				break ;
			i++;
			j++;
			if (nee[j] == 0)
				return (&hay[i - j]);
		}
		i = k + 1;
		len--;
		j = 0;
	}
	return (NULL);
}
