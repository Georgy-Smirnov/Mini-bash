/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:01:43 by kjaco             #+#    #+#             */
/*   Updated: 2021/04/01 20:07:41 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	put_count_bytes_in_strs(char const *s1, char const *s2)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s1[i])
	{
		count++;
		i++;
	}
	i = 0;
	while (s2[i])
	{
		count++;
		i++;
	}
	return (count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rezult;
	int		i;
	int		count;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	count = put_count_bytes_in_strs(s1, s2);
	rezult = malloc((count + 1) * sizeof(char));
	if (rezult == NULL)
		return (NULL);
	count = 0;
	while (s1[i])
	{
		rezult[count] = s1[i++];
		count++;
	}
	i = 0;
	while (s2[i])
	{
		rezult[count] = s2[i++];
		count++;
	}
	rezult[count] = '\0';
	return (rezult);
}
