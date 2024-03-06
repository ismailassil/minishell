/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cont_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:25:31 by iassil            #+#    #+#             */
/*   Updated: 2024/03/06 19:25:33 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_t_cont_len(t_cont *head)
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

static t_cont	*ft_last_node(t_cont *top)
{
	while (top->next)
	{
		top = top->next;
	}
	return (top);
}

static t_cont	*ft_new_node(char *token)
{
	t_cont	*new;

	new = malloc(sizeof(t_cont));
	if (!new)
		return (NULL);
	new->token = ft_strdup(token);
	if (!new->token)
		return (NULL);
	new->next = NULL;
	return (new);
}

int	ft_push_token(char *token, t_cont **head)
{
	t_cont	*newnode;
	t_cont	*last;

	newnode = ft_new_node(token);
	if (!newnode)
		return (0);
	if (!head || !(*head))
		*head = newnode;
	else
	{
		last = ft_last_node(*head);
		last->next = newnode;
	}
	return (1);
}

void	ft_free_tokens(t_cont **head)
{
	t_cont	*current;

	while (*head)
	{
		current = *head;
		free(current->token);
		current->token = NULL;
		free(current);
		current = NULL;
		*head = (*head)->next;
	}
}
