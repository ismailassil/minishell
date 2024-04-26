/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:37:37 by aibn-che          #+#    #+#             */
/*   Updated: 2024/04/26 10:08:59 by iassil           ###   ########.fr       */
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
int	ft_check_file_name(t_file *hold)
{
	int		i;
	int		j;
	int		flag;
	t_file	*head;

	head = hold;
	while (head != NULL)
	{
		(1) && (i = 0, j = 0, flag = 0);
		if (ft_strchr(head->before, '$') && !ft_strchr(head->before, '"')
			&& !ft_strchr(head->before, '\'') && head->after[0] == '\0')
			return (head->status = 1, 1);
		while (head->before && head->before[i] != '\0')
		{
			if (ft_occurence_of_amb(head, &flag, &i, &j))
				return (1);
			if (head->before[i])
				i++;
		}
		head = head->next;
	}
	return (0);
}
