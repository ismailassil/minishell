/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:47 by iassil            #+#    #+#             */
/*   Updated: 2024/02/27 16:29:10 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstiter(t_container *lst, void (*f)(void *))
{
	t_container	*ptr;

	if (lst == NULL || f == NULL)
		return ;
	ptr = lst;
	while (ptr != NULL)
	{
		f(ptr->holder);
		ptr = ptr->next;
	}
}
