/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:31:59 by kjaco             #+#    #+#             */
/*   Updated: 2021/04/01 20:08:05 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	all_free(char **rez, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(rez[i]);
		i++;
	}
	free(rez);
}

int	count_word(char const *s, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
			k++;
		i++;
	}
	return (k);
}

char	**allocate_memory(char *s, char c)
{
	char	**rez;
	int		j;
	int		k;

	rez = (char **)malloc((count_word(s, c) + 1) * sizeof(char *));
	if (rez == NULL)
		return (NULL);
	j = 0;
	while (*s)
	{
		k = 0;
		while (*s && *s == c)
			s++;
		while (*s && *(s++) != c)
			k++;
		if (k)
		{
			rez[j] = (char *)malloc((k + 1) * sizeof(char));
			if (rez == NULL)
				all_free(rez, count_word(s, c));
			j++;
		}
	}
	rez[j] = NULL;
	return (rez);
}

char	**ft_split(char const *s, char c)
{
	char	**rez;
	int		i;
	int		j;
	int		k;

	if (!s)
		return (NULL);
	rez = allocate_memory((char *)s, c);
	if (rez == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		k = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
			rez[j][k++] = s[i++];
		if (k)
			rez[j][k] = 0;
		j++;
	}
	return (rez);
}
