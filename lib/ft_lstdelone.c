/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:34:47 by iassil            #+#    #+#             */
/*   Updated: 2024/03/06 21:12:00 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstdelone(t_cont *lst, void (*del)(void *))
{
	t_cont	*ptr;

	if (lst == NULL || del == NULL)
		return ;
	ptr = lst;
	lst = lst->next;
	del(ptr->cmd);
	free(ptr);
	ptr = NULL;
}
