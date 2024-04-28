/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:52:06 by aibn-che          #+#    #+#             */
/*   Updated: 2024/04/28 15:20:21 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_t_token_len(t_token *head)
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

t_token	*ft_last_node(t_token *top)
{
	while (top && top->next)
	{
		top = top->next;
	}
	return (top);
}

t_token	*ft_new_node(char *token)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	ft_check_allocation(new);
	new->token = ft_strdup(token);
	new->is_var = 0;
	new->is_quote = 0;
	if (!new->token)
		return (NULL);
	new->next = NULL;
	return (new);
}

int	ft_push_token(char *token, t_token **head)
{
	t_token	*newnode;
	t_token	*last;

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

void	ft_free_tokens(t_token **head)
{
	t_token	*current;

	current = NULL;
	while (*head)
	{
		current = *head;
		*head = (*head)->next;
		free(current->token);
		current->token = NULL;
		free(current);
		current = NULL;
	}
	free(*head);
	*head = NULL;
}
