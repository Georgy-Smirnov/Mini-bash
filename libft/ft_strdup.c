/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 22:19:36 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/10 12:38:47 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	char	*cp;
	int		i;

	i = 0;
	while (s[i])
		i++;
	if (s[i] == 0)
		i++;
	cp = (char *)malloc(sizeof(char) * i);
	if (cp == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		cp[i] = s[i];
		i++;
	}
	if (s[i] == 0)
		cp[i] = 0;
	return (cp);
}
