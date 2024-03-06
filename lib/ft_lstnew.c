/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:18:17 by iassil            #+#    #+#             */
/*   Updated: 2024/03/02 17:23:30 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cont	*ft_lstnew(void *content)
{
	t_cont	*head;

	head = (t_cont *)malloc(sizeof(t_cont));
	if (head == NULL)
		return (NULL);
	head->holder = content;
	head->next = NULL;
	return (head);
}
