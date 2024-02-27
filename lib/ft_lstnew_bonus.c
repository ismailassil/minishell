/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:18:17 by iassil            #+#    #+#             */
/*   Updated: 2024/02/27 16:28:46 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_container	*ft_lstnew(void *content)
{
	t_container	*head;

	head = (t_container *)malloc(sizeof(t_container));
	if (head == NULL)
		return (NULL);
	head->holder = content;
	head->next = NULL;
	return (head);
}
