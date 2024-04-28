/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_after_expanding.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:36:23 by iassil            #+#    #+#             */
/*   Updated: 2024/04/28 15:48:37 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_trim_special_quote(char *str)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	ptr = NULL;
	while (str && str[i])
	{
		if (str[i] == SQ)
			j++;
		i++;
	}
	ptr = malloc((i - j + 1) * sizeof(char));
	ft_check_allocation(ptr);
	(1) && (i = 0, j = 0);
	while (str && str[i])
	{
		if (str[i] == SQ)
			i++;
		else
			ptr[j++] = str[i++];
	}
	ptr[j] = '\0';
	return (ptr);
}

void	ft_fill_new_ptr_(char ***new_ptr, char **big_ptr)
{
	int	i;
	int	j;

	(1) && (i = 0, j = 0);
	while (big_ptr && big_ptr[i])
	{
		if (big_ptr[i][0] == '\0')
			i++;
		else
			(*new_ptr)[j++] = ft_strdup(big_ptr[i++]);
	}
	(*new_ptr)[j] = 0;
}

void	ft_skip_null_arg(char ***big_ptr)
{
	char	**new_ptr;
	int		i;
	int		j;

	(1) && (i = 0, j = 0);
	if (!big_ptr || !*big_ptr)
		return ;
	while (big_ptr && *big_ptr && (*big_ptr)[i])
	{
		if ((*big_ptr)[i][0] == '\0')
			j++;
		i++;
	}
	new_ptr = malloc((i - j + 1) * sizeof(char *));
	ft_check_allocation(new_ptr);
	ft_fill_new_ptr_(&new_ptr, *big_ptr);
	ft_f(*big_ptr);
	*big_ptr = new_ptr;
}

char	**ft_split_after_expanding(char *str)
{
	char	**big_ptr;
	char	*tmp;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	big_ptr = ft_split_vquote(str);
	while (big_ptr && big_ptr[i])
	{
		if (ft_strchr(big_ptr[i], SQ))
		{
			tmp = ft_trim_special_quote(big_ptr[i]);
			free(big_ptr[i]);
			big_ptr[i] = ft_strdup(tmp);
			free(tmp);
			flag = 1;
		}
		i++;
	}
	ft_skip_null_arg(&big_ptr);
	return (big_ptr);
}
