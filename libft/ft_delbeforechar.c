/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delbeforechar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:56:14 by kjaco             #+#    #+#             */
/*   Updated: 2021/04/01 20:08:23 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_delbeforechar(char a, char *str)
{
	char	*rez;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != a)
		i++;
	i++;
	while (str[j])
		j++;
	rez = (char *)malloc(sizeof(char) * (j - i + 1));
	if (rez == NULL)
		return (NULL);
	j = 0;
	while (str[i + j])
	{
		rez[j] = str[i + j];
		j++;
	}
	rez[j] = 0;
	free(str);
	return (rez);
}

int	charinstr(char a, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == a)
			return (i);
		i++;
	}
	return (-1);
}
