/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_after_expanding.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:36:23 by iassil            #+#    #+#             */
/*   Updated: 2024/04/25 22:04:21 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_quotes(char *str)
{
	t_tools	d;

	(1) && (d.i = 0, d.flag = 0, d.count = 0, d.cquote = 0);
	while (str && str[d.i] != '\0')
	{
		if (str[d.i] == '"' || str[d.i] == '\'')
		{
			d.quote = str[d.i];
			d.flag = 1;
			d.cquote++;
			d.i++;
		}
		while (d.flag == 1 && str[d.i] != d.quote && str[d.i] != '\0')
			d.i++;
		if (d.flag == 1 && str[d.i] == d.quote)
			(1) && (d.flag = 0, d.quote = 0);
		if (str[d.i])
			d.i++;
	}
	return (d.i + (d.cquote * 2));
}

char	**ft_split_after_expanding(char *str)
{
	char	**big_ptr;
	char	*tmp;
	int		i;

	i = 0;
	big_ptr = ft_split_vquote(str);
	while (big_ptr && big_ptr[i])
	{
		if (ft_strchr(big_ptr[i], '\"') || ft_strchr(big_ptr[i], '\"'))
		{
			tmp = ft_trim_quotes(big_ptr[i]);
			free(big_ptr[i]);
			big_ptr[i] = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
	return (big_ptr);
}
