/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:38:05 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/10 11:49:33 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*rezult;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	if (start > i)
	{
		rezult = (char *)malloc(sizeof(char));
		*rezult = 0;
		return (rezult);
	}
	if (start + (unsigned int)len > i)
		rezult = (char *)malloc((size_t)(i - start + 1) * sizeof(char));
	else
		rezult = (char *)malloc((len + 1) * sizeof(char));
	if (rezult == NULL)
		return (NULL);
	i = 0;
	while (len-- && s[start])
		rezult[i++] = s[start++];
	rezult[i] = '\0';
	return (rezult);
}
