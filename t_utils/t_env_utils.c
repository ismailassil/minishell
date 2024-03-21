/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 19:19:08 by iassil            #+#    #+#             */
/*   Updated: 2024/03/21 22:38:10 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_t_env_len(t_env *head)
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

static t_env	*ft_last_node(t_env *top)
{
	while (top->next)
		top = top->next;
	return (top);
}

static t_env	*ft_new_node(char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	if (!new->value)
		return (NULL);
	new->next = NULL;
	return (new);
}

int	ft_push_value(char *value, t_env **head)
{
	t_env	*newnode;
	t_env	*last;

	newnode = ft_new_node(value);
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

void	ft_free_env(t_env **head)
{
	t_env	*current;

	while (*head)
	{
		current = *head;
		*head = (*head)->next;
		free(current->value);
		current->value = NULL;
		free(current);
	}
}
