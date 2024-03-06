/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:41:50 by iassil            #+#    #+#             */
/*   Updated: 2024/03/06 19:24:56 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	create a function that create a node that holds what inside the t_cont
void	ft_link_for_container(t_token *token, t_cont **container)
{
	t_token	*head;
	t_cont	*cont;

	head = token;
	cont = *container;
	while (head != NULL)
	{
		if (head->type == CMD)
		{
			
		}
		head = head->next;
	}
}

void	ft_execute_one_cmd(t_cont *container)
{
	
}

void	ft_execution(t_token **token)
{
	t_token			*head;
	t_cont			*container;
	unsigned int	nbr_cmd;

	head = *token;
	nbr_cmd = 0;
	while (head)
	{
		if (head->type == CMD)
			nbr_cmd++;
		head = head->next;
	}
	ft_link_for_container(*token, &container);
	ft_free_tokens(token);
	if (nbr_cmd == 0)
		ft_execute_one_cmd(container);
}
