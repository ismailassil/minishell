/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils_v3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:24:39 by iassil            #+#    #+#             */
/*   Updated: 2024/04/22 11:03:43 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_there(char *del)
{
	int	i;

	i = 0;
	if (!ft_strchr(del, '$') && (!ft_strchr(del, '"') || !ft_strchr(del, '"')))
		return (1);
	while (del[i] != '\0')
	{
		if (del[i] == '$' && (del[i + 1] == '"' || del[i + 1] == '\''))
			return (0);
		i++;
	}
	return (1);
}

char	*ft_check_delimiter(char *del)
{
	t_del	d;

	(1) && (d.i = 0, d.j = 0, d.flag = 0, d.count = 0, d.len = 0, d.quote = 0);
	if (ft_is_there(del))
		return (ft_strdup(del));
	while (del[d.len])
	{
		if (del[d.len] == '$' && del[d.len + 1] == '"')
			d.count++;
		d.len++;
	}
	d.ptr = malloc((ft_strlen(del) - (d.count * 3) + 2) * sizeof(char));
	ft_check_allocation(d.ptr);
	while (del[d.i] != '\0')
	{
		if (del[d.i] == '$' && (del[d.i + 1] == '"' || del[d.i + 1] == '\''))
			(1) && (d.i += 2, d.flag = 1, d.quote = del[d.i + 1]);
		if (d.flag == 1 && del[d.i] == d.quote)
			(1) && (d.i++, d.flag = 0, d.quote = 0);
		if (del[d.i])
			d.ptr[d.j++] = del[d.i++];
	}
	d.ptr[d.j] = '\0';
	return (d.ptr);
}
