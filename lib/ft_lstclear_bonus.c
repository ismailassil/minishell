/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:39:57 by iassil            #+#    #+#             */
/*   Updated: 2024/02/27 16:29:02 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear(t_container **lst, void (*del)(void *))
{
	t_container	*ptr;
	t_container	*index;

	if (lst == NULL || del == NULL)
		return ;
	ptr = *lst;
	while (ptr != NULL)
	{
		index = ptr->next;
		del(ptr->holder);
		free(ptr);
		ptr = index;
	}
	if (*lst != NULL)
		*lst = NULL;
}
