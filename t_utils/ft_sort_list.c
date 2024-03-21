/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:45:28 by iassil            #+#    #+#             */
/*   Updated: 2024/03/21 15:55:14 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sort_list(t_env **env)
{
	t_env	*first;
	t_env	*second;
	char	*tmp;

	first = *env;
	while (first != NULL && first->next != NULL)
	{
		second = *env;
		while (second != NULL && second->next != NULL)
		{
			if (ft_strcmp(second->value, second->next->value) > 0)
			{
				tmp = second->value;
				second->value = second->next->value;
				second->next->value = tmp;
			}
			second = second->next;
		}
		first = first->next;
	}
}
