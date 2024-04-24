/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:37:37 by aibn-che          #+#    #+#             */
/*   Updated: 2024/04/24 23:07:32 by iassil           ###   ########.fr       */
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

bool	ft_check_is_amb(t_file *head, int index)
{
	char	**ptr;
	int		i;

	ptr = NULL;
	i = 0;
	if (head->vars && head->vars[index])
	{
		if (head->vars[index] && ft_contain_spaces(head->vars[index]))
			return (true);
		ptr = ft_split_v2(head->vars[index]);
		ft_check_allocation(ptr);
		while (ptr && ptr[i])
			i++;
		ft_f(ptr);
		if (i > 1)
			return (true);
	}
	return (false);
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
	int		quote;
	int		flag;
	t_file	*head;

	head = hold;
	while (head != NULL)
	{
		(1) && (i = 0, j = 0, flag = 0);
		if (ft_strchr(head->before, '$') && !ft_strchr(head->before, '"') && !ft_strchr(head->before, '\'') && head->after[0] == '\0')
			return (head->status = 1, 1);
		while (head->before && head->before[i] != '\0')
		{
			if (flag == 0 && head->before[i] && (head->before[i] == '"' || head->before[i] == '\''))
				(1) && (quote = head->before[i], flag = 1, i++);
			while (flag == 1 && head->before[i] && head->before[i] != quote)
				if (head->before[i++] == '$')
					j++;
			while (flag == 0 && head->before[i] && head->before[i] != '"' && head->before[i] != '\'')
			{
				if (head->before[i] && head->before[i] == '$')
				{
					if ((ft_strchr(head->before, '\'') || ft_strchr(head->before, '"')) && head->after[0] == '\0')
						;
					else if (ft_check_is_amb(head, j))
						return (head->status = 1, 1);
					j++;
				}
				i++;
			}
			if (flag == 1 && head->before[i] && head->before[i] == quote)
				(1) && (quote = 0, flag = 1, i++);
			if (!head->before[i])
				break ;
		}
		head = head->next;
	}
	return (ft_free_t_file(&hold), 0);
}

	// while (head != NULL)
	// {
	// 	int	i = 0;
	// 	// while (head->vars && head->vars[i])
	// 	// 	printf("{%s}\n", head->vars[i++]);
	// 	if (ft_contain_quotes(head->before) && head->after[0] == '\0')
	// 	{
	// 		return (head->status = 2, 1);
	// 	}
	// 	if (head->after[0] == '\0' || ft_contain_spaces(head->after))
	// 	{
	// 		return (head->status = 1, 1);
	// 	}
	// 	head = head->next;
	// }