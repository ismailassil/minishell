/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:24:38 by iassil            #+#    #+#             */
/*   Updated: 2024/03/06 21:12:23 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cont	*ft_lstmap(t_cont *lst, void *(*f)(void *),
	void (*del)(void *))
{
	t_cont	*ptr;
	t_cont	*current;
	t_cont	*new_list;

	if (lst == NULL || del == NULL || f == NULL)
		return (NULL);
	current = NULL;
	new_list = NULL;
	ptr = lst;
	while (ptr != NULL)
	{
		current = ft_lstnew(NULL);
		if (current == NULL)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		current->cmd = f(ptr->cmd);
		ft_lstadd_back(&new_list, current);
		ptr = ptr->next;
	}
	return (new_list);
}
