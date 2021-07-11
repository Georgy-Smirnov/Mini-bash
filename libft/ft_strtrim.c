/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:54:39 by kjaco             #+#    #+#             */
/*   Updated: 2021/04/01 20:07:06 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	search_start(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		while (set[j])
		{
			if (s1[i] == set[j])
				break ;
			j++;
		}
		if (s1[i] != set[j])
			break ;
		j = 0;
		i++;
	}
	return (i);
}

int	search_end(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	k;

	i = ft_strlen((char *)s1) - 1;
	j = 0;
	k = 0;
	while (i)
	{
		while (set[j])
		{
			if (s1[i] == set[j])
				break ;
			j++;
		}
		if (s1[i] != set[j])
			break ;
		j = 0;
		i--;
		k++;
	}
	return (k);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*rez;
	int		i;
	int		count;
	int		count_start;
	int		count_end;

	if (!s1 || !set)
		return (NULL);
	count_start = search_start(s1, set);
	count_end = search_end(s1, set);
	count = ft_strlen((char *)s1) - count_start - count_end;
	if (count < 0)
		count = 0;
	rez = (char *)malloc((count + 1) * sizeof(char));
	if (rez == NULL)
		return (NULL);
	i = 0;
	while (count--)
	{
		rez[i] = s1[count_start];
		i++;
		count_start++;
	}
	rez[i] = 0;
	return (rez);
}
