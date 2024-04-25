/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file_name_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:34:38 by aibn-che          #+#    #+#             */
/*   Updated: 2024/04/25 18:39:38 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

bool	ft_is_word(char *str)
{
	int	i;
	int	flag;
	int	quote;

	i = 0;
	flag = 0;
	quote = 0;
	while (str && str[i])
	{
		if (flag == 0 && str[i] && (str[i] == '\'' || str[i] == '\"'))
		{
			(1) && (quote = str[i], i++);
			while (str[i] != '\0' && str[i] != quote)
			{
				if (str[i] && ft_isalnum(str[i]))
					return (false);
				i++;
			}
			if (str[i])
				i++;
		}
		if (str[i])
			i++;
	}
	return (true);
}

bool	ft_check_is_amb(t_file *head, int index)
{
	char	**ptr;
	int		i;

	ptr = NULL;
	i = 0;
	if (head->vars && head->vars[index])
	{
		if (head->vars[index] && ft_contain_spaces(head->vars[index])
			&& ft_is_word(head->after))
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

int	ft_occurence_of_amb(t_file	*head, int *flag, int *i, int *j)
{
	int	quote;

	if ((*flag) == 0 && head->before[(*i)]
		&& (head->before[(*i)] == '"' || head->before[(*i)] == '\''))
		(1) && (quote = head->before[(*i)], (*flag) = 1, (*i)++);
	while ((*flag) == 1 && head->before[(*i)] && head->before[(*i)] != quote)
		if (head->before[(*i)++] == '$')
			(*j)++;
	while ((*flag) == 0 && head->before[(*i)] && head->before[(*i)] != '"'
		&& head->before[(*i)] != '\'')
	{
		if (head->before[(*i)] && head->before[(*i)] == '$')
		{
			if ((ft_strchr(head->before, '\'') || ft_strchr(head->before, '"'))
				&& head->after[0] == '\0')
				;
			else if (ft_check_is_amb(head, (*j)))
				return (head->status = 1, 1);
			(*j)++;
		}
		(*i)++;
	}
	if ((*flag) == 1 && head->before[(*i)] && head->before[(*i)] == quote)
		(1) && (quote = 0, (*flag) = 1, (*i)++);
	return (0);
}
