/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:03:44 by iassil            #+#    #+#             */
/*   Updated: 2024/02/27 16:20:34 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_count_digits(long long n)
{
	size_t	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static void	ft_convert(char *ptr, long long n, int size)
{
	if (n < 0)
	{
		ptr[0] = '-';
		n = -n;
	}
	size--;
	while (n)
	{
		ptr[size] = (n % 10) + '0';
		n /= 10;
		size--;
	}
}

char	*ft_itoa(int n)
{
	size_t		i;
	size_t		size;
	char		*ptr;
	long long	z;

	i = 0;
	z = (long long)n;
	size = ft_count_digits(z);
	ptr = (char *)ft_calloc((size + 1), sizeof(char));
	if (ptr == NULL)
		return (NULL);
	if (z == 0)
	{
		*ptr = '0';
		return (ptr);
	}
	ft_convert(ptr, z, size);
	return (ptr);
}
