/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils_v3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:24:39 by iassil            #+#    #+#             */
/*   Updated: 2024/04/23 19:25:06 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	ft_check_before_trim(char *del)
{
	int	i;

	i = 0;
	while (del && del[i] != '\0')
	{
		if (del[i] == '$' && (del[i + 1] == '"' || del[i + 1] == '\''))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_allocate_for_new_trim(char *del)
{
	t_del	d;

	(1) && (d.i = 0, d.j = 0, d.count = 0, d.len = 0, d.flag = 0, d.quote = 0);
	while (del && del[d.i] != '\0')
	{
		if (del[d.i] && d.flag == 0 && (del[d.i] == '"' || del[d.i] == '\''))
		{
			if (d.i > 0 && del[d.i - 1] == '$')
				d.len++;
			d.quote = del[d.i];
			d.flag = 1;
			d.i++;
			d.count++;
		}
		while (del[d.i] && d.flag == 1 && del[d.i] != d.quote)
			d.i++;
		if (del[d.i] && d.flag == 1 && del[d.i] == d.quote)
			(1) && (d.flag = 0, d.quote = 0);
		if (del[d.i])
			d.i++;
	}
	return (d.i + (d.count * 2) - d.len);
}

char	*ft_trim_dollar(char *del)
{
	t_del	d;

	(1) && (d.i = 0, d.j = 0, d.count = 0, d.len = 0, d.flag = 0, d.quote = 0);
	if (ft_check_before_trim(del))
		return (ft_trim_quotes(del));
	d.len = ft_allocate_for_new_trim(del);
	d.ptr = malloc((d.len + 1) * sizeof(char));
	ft_check_allocation(d.ptr);
	while (del && del[d.i] != '\0')
	{
		if (del[d.i] && d.flag == 0 && del[d.i] == '$'
			&& (del[d.i + 1] == '"' || del[d.i + 1] == '\''))
			d.i++;
		if (del[d.i] && d.flag == 0 && (del[d.i] == '"' || del[d.i] == '\''))
			(1) && (d.quote = del[d.i], d.flag = 1, d.i++);
		while (del[d.i] && d.flag == 1 && del[d.i] != d.quote)
			d.ptr[d.j++] = del[d.i++];
		if (del[d.i] && d.flag == 1 && del[d.i] == d.quote)
			(1) && (d.flag = 0, d.is_dollar = 0, d.quote = 0, d.i++);
		if (del[d.i] && del[d.i] != '\'' && del[d.i] != '"')
			d.ptr[d.j++] = del[d.i++];
	}
	d.ptr[d.j] = '\0';
	return (d.ptr);
}

bool	ft_check_del_and_quotes(char *hold)
{
	if (ft_strchr(hold, '"') || ft_strchr(hold, '\'') || ft_strchr(hold, '$'))
		return (1);
	return (0);
}

char	*ft_remove_for_del(char *hold)
{
	if ((ft_strchr(hold, '"') || ft_strchr(hold, '\''))
		&& !ft_strchr(hold, '$'))
		return (ft_trim_quotes(hold));
	if (ft_strchr(hold, '$') && (ft_strchr(hold, '\'')
			|| ft_strchr(hold, '"')))
		return (ft_trim_dollar(hold));
	return (ft_strdup(hold));
}
