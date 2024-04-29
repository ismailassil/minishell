/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils_v2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 23:02:17 by iassil            #+#    #+#             */
/*   Updated: 2024/04/29 15:39:24 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_between_quotesorequal(char *str, int f)
{
	int	i;
	int	flag;
	int	quotes;
	int	equal;

	i = 0;
	flag = 0;
	quotes = 0;
	equal = 0;
	while (str && str[i] != '\0')
	{
		if (flag == 0 && str[i] == '=' && f == 1)
			(1) && (equal = str[i], flag = 1, i++);
		if (flag == 0 && str[i] == SQ)
			(1) && (quotes = str[i], flag = 2, i++);
		while (flag == 1 && str[i])
			if (str[i++] == '$')
				return (1);
		while (flag == 2 && str[i] && str[i] != quotes)
			if (str[i++] == '$')
				return (1);
		if (str[i])
			i++;
	}
	return (0);
}
