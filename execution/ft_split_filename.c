/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_filname.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:36:23 by iassil            #+#    #+#             */
/*   Updated: 2024/04/24 19:20:21 by iassil           ###   ########.fr       */
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

char	*ft_add_space(char *str, int len)
{
	t_tools	d;

	(1) && (d.i = 0, d.j = 0, d.flag = 0, d.cquote = 0, d.quote = 0);
	d.ptr = malloc((len + 1) * sizeof(char *));
	ft_check_allocation(d.ptr);
	while (str && str[d.i] != '\0')
	{
		if (str[d.i] == '"' || str[d.i] == '\'')
		{
			(1) && (d.quote = str[d.i], d.flag = 1);
			d.ptr[d.j++] = ' ';
			d.ptr[d.j++] = str[d.i++];
		}
		while (d.flag == 1 && str[d.i] != d.quote && str[d.i] != '\0')
			d.ptr[d.j++] = str[d.i++];
		if (d.flag == 1 && str[d.i] == d.quote)
		{
			(1) && (d.flag = 0, d.quote = 0);
			(1) && (d.ptr[d.j++] = str[d.i++], d.ptr[d.j++] = ' ');
		}
		if (str[d.i])
			d.ptr[d.j++] = str[d.i++];
	}
	d.ptr[d.j] = '\0';
	return (d.ptr);
}

char	**ft_split_filename(char *str)
{
	int		len;
	char	*ptr;
	char	**big_ptr;

	len = ft_count_quotes(str);
	if (!len)
		return (NULL);
	ptr = ft_add_space(str, len);
	big_ptr = ft_split_vquote(ptr, ' ');
	return (big_ptr);
}
