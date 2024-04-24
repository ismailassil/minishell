/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:37:37 by aibn-che          #+#    #+#             */
/*   Updated: 2024/04/24 20:16:50 by aibn-che         ###   ########.fr       */
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

int	ft_contain_spaces(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && ft_strchr(" \t\n\v\f\r", str[i]))
		i++;
	if (str && !str[i])
		return (1);
	while (str && str[i] && !ft_strchr(" \t\n\v\f\r", str[i]))
		i++;
	while (str && str[i])
	{
		if (!ft_strchr(" \t\n\v\f\r", str[i]))
			return (1);
		i++;
	}
	return (0);
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
int	ft_check_file_name(t_file *head)
{
	while (head != NULL)
	{
		if (ft_contain_quotes(head->before) && head->after[0] == '\0')
		{
			return (head->status = 2, 1);
		}
		if (head->after[0] == '\0' || ft_contain_spaces(head->after))
		{
			return (head->status = 1, 1);
		}
		head = head->next;
	}
	return (0);
}
