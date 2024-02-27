/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:45:10 by iassil            #+#    #+#             */
/*   Updated: 2024/02/27 16:28:20 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_container	*ft_lstlast(t_container *lst)
{
	t_container	*ptr;

	if (lst == NULL)
		return (NULL);
	ptr = lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}
