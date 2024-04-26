/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:18:17 by iassil            #+#    #+#             */
/*   Updated: 2024/04/26 11:29:35 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cont	*ft_lstnew(void *content)
{
	t_cont	*head;

	head = (t_cont *)malloc(sizeof(t_cont));
	ft_check_allocation(head);
	head->cmd = content;
	head->next = NULL;
	return (head);
}
