/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:47:36 by iassil            #+#    #+#             */
/*   Updated: 2024/03/21 17:20:05 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *str, int c)
{
	while (str && *str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	return (0);
}
