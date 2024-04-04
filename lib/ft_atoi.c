/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:25:23 by iassil            #+#    #+#             */
/*   Updated: 2024/04/04 00:33:59 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_isspace_(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	ft_sign(const char *str, size_t *i)
{
	int	sign;

	sign = 1;
	if (str && (str[*i] == '-' || str[*i] == '+'))
	{
		if (str[*i] == '-')
			sign *= -1;
		(*i)++;
	}
	return (sign);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	long	result;
	long	res1;
	int		sign;

	i = 0;
	result = 0;
	while (str && ft_isspace_(str[i]) == 1)
		i++;
	sign = ft_sign(str, &i);
	while (str && ft_isdigit(str[i]) > 0)
	{
		res1 = (result * 10) + (str[i] - 48);
		if (result > res1 && sign == 1)
			return (-1);
		else if (result > res1 && sign == -1)
			return (0);
		result = res1;
		i++;
	}
	return (result * sign);
}

static int	ft__is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

unsigned long long	ft__atoi(const char *str)
{
	int						i;
	unsigned long long int	res;
	int						sign;

	i = 0;
	sign = 1;
	while (str && ft__is_space(str[i]))
		i++;
	res = 0;
	if (str && (str[i] == '+' || str[i] == '-'))
		if (str[i++] == '-')
			sign *= -1;
	while (str && ft_isdigit(str[i]))
	{
		res = (10 * res) + (str[i] - '0');
		if ((sign == 1) && (res > __LONG_MAX__))
			return (9223372036854775808ULL);
		if ((sign == -1) && (res > 9223372036854775808ULL))
			return (9223372036854775809ULL);
		i++;
	}
	return (res);
}
