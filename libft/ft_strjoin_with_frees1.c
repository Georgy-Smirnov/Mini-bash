/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_with_frees1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:53:30 by kjaco             #+#    #+#             */
/*   Updated: 2021/04/01 20:07:27 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	put_count_bytes_in_str(char *s1, char *s2)
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

char	*ft_strjoin_with_frees1(char *s1, char *s2)
{
	char	*rezult;
	int		i;
	int		count;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	rezult = malloc((put_count_bytes_in_str(s1, s2) + 1) * sizeof(char));
	if (rezult == NULL)
	{
		free(s1);
		return (NULL);
	}
	count = 0;
	while (s1[i])
		rezult[count++] = s1[i++];
	i = 0;
	while (s2[i])
		rezult[count++] = s2[i++];
	rezult[count] = '\0';
	free(s1);
	return (rezult);
}
