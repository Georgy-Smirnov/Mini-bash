/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 20:19:46 by kjaco             #+#    #+#             */
/*   Updated: 2020/11/21 19:36:24 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*rez;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	rez = (char *)malloc((i + 1) * sizeof(char));
	if (rez == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		rez[i] = f(i, s[i]);
		i++;
	}
	rez[i] = 0;
	return (rez);
}
