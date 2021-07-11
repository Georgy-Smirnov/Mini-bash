/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:00:13 by kjaco             #+#    #+#             */
/*   Updated: 2021/04/01 20:08:47 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ten_in_pow(int pow)
{
	int	rez;

	rez = 1;
	while (pow)
	{
		rez *= 10;
		pow--;
	}
	return (rez);
}

int	count_digit_in_num(long long n)
{
	int	count;

	count = 0;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*fill_str(char *rez, long long n)
{
	int	i;
	int	count_digit;

	i = 0;
	if (n < 0)
	{
		rez[i] = '-';
		i++;
		n = -n;
	}
	if (n == 0)
	{
		rez[i] = '0';
		rez[i + 1] = 0;
		return (rez);
	}
	count_digit = count_digit_in_num(n);
	while (count_digit--)
	{
		rez[i++] = (n / ten_in_pow(count_digit)) + 48;
		n %= ten_in_pow(count_digit);
	}
	rez[i] = 0;
	return (rez);
}

char	*ft_itoa(int n)
{
	int			count_bytes;
	char		*rez;
	long long	ln;

	ln = (long long)n;
	count_bytes = 1;
	if (n <= 0)
		count_bytes++;
	count_bytes += count_digit_in_num(n);
	rez = (char *)malloc(count_bytes * sizeof(char));
	if (rez == NULL)
		return (NULL);
	rez = fill_str(rez, ln);
	return (rez);
}
