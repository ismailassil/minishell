/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:34:47 by iassil            #+#    #+#             */
/*   Updated: 2024/02/27 16:28:55 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstdelone(t_container *lst, void (*del)(void *))
{
	t_container	*ptr;

	if (lst == NULL || del == NULL)
		return ;
	ptr = lst;
	lst = lst->next;
	del(ptr->holder);
	free(ptr);
	ptr = NULL;
}
