/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:37:37 by aibn-che          #+#    #+#             */
/*   Updated: 2024/04/26 16:07:19 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_back(t_file **lst, t_file *_new)
{
	t_file	*ptr;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = _new;
		return ;
	}
	ptr = *lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = _new;
}

int	ft_contain_quotes(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

typedef struct s_check_filename
{
	int		i;
	int		j;
	int		flag;
	t_file	*head;
	char	*tmp;
}			t_check_filename;

/*
 * Checking by file_name
 * 
 * 1 => for ambiguous redirect
 	(when the variable name not exist)
	|| var is null
*
 * 2 => for No such file or directory
 	(when the variable name not exist And enclosed with double quotes)
	|| var is null
*
 * 0 => for regulare outfile
*/

int	ft_check_if_splitted(char **str)
{
	char	**ptr;
	int		i;
	int		count;

	if (!ft_strchr(*str, SQ))
		return (0);
	i = 0;
	count = 0;
	ptr = ft_split_vquote(*str);
	while (ptr && ptr[i])
	{
		if (ptr[i][0] == '\0' || (ptr[i][0] == SQ && ptr[i][1] == SQ))
			i++;
		else
			(1) && (i++, count++);
	}
	ft_f(ptr);
	if (count > 1)
		return (1);
	return (0);
}

int	ft_check_file_name(t_file *hold)
{
	t_check_filename	f;

	f.head = hold;
	while (f.head != NULL)
	{
		(1) && (f.i = 0, f.j = 0, f.flag = 0);
		if (ft_check_if_splitted(&f.head->after))
			return (f.head->status = 1, 1);
		ft_check_special_quote(&f.head->after);
		if (ft_strchr(f.head->before, '$') && !ft_strchr(f.head->before, '"')
			&& !ft_strchr(f.head->before, '\'') && f.head->after[0] == '\0')
			return (f.head->status = 1, 1);
		while (f.head->before && f.head->before[f.i] != '\0')
		{
			if (ft_occurence_of_amb(f.head, &f.flag, &f.i, &f.j))
				return (1);
			if (f.head->before[f.i])
				f.i++;
		}
		f.head = f.head->next;
	}
	return (0);
}
