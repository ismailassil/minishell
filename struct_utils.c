/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:52:06 by aibn-che          #+#    #+#             */
/*   Updated: 2024/03/01 18:42:09 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	stack_len(t_token *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

t_token	*last_node(t_token *top)
{
	while (top->next)
	{
		top = top->next;
	}
	return (top);
}

t_token	*new_node(char *token)
{
	t_token	*new;
	static int		id;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = token;
	new->next = NULL;
	return (new);
}

int	push(char *token, t_token **head)
{
	t_token	*newnode;
	t_token	*last;

	newnode = new_node(token);
	if (!newnode)
		return (0);
	if (!head || !(*head))
		*head = newnode;
	else
	{
		last = last_node(*head);
		last->next = newnode;
	}
	return (1);
}

void	free_linked_list(t_token **head)
{
	t_token	*current;

	while (*head)
	{
		current = *head;
		*head = (*head)->next;
		free(current);
	}
}
