/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cont_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:25:31 by iassil            #+#    #+#             */
/*   Updated: 2024/03/06 21:14:18 by iassil           ###   ########.fr       */
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
		top = top->next;
	return (top);
}

static void	ft_allocate_for_the_rest(t_tmp_cont *tmp, t_cont **new)
{
	int	i;

	i = 0;
	while (*(tmp->arg) != 0)
	{
		(*new)->arg[i] = ft_strdup(tmp->arg[i]);
		i++;
	}
	i = 0;
	while (*(tmp->infile) != 0)
	{
		(*new)->infile[i] = ft_strdup(tmp->infile[i]);
		i++;
	}
	i = 0;
	while (*(tmp->outfile) != 0)
	{
		(*new)->outfile[i] = ft_strdup(tmp->outfile[i]);
		i++;
	}
}

static t_cont	*ft_new_node(t_tmp_cont *tmp)
{
	t_cont	*new;

	new = malloc(sizeof(t_cont));
	if (!new)
		return (NULL);
	new->cmd = ft_strdup(tmp->cmd);
	if (!new->cmd)
		(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
	ft_allocate_for_the_rest(tmp, &new);
	new->next = NULL;
	return (new);
}

int	ft_push_container(t_tmp_cont *tmp, t_cont **head)
{
	t_cont	*newnode;
	t_cont	*last;

	newnode = ft_new_node(tmp);
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

void	ft_free_containers(t_cont **head)
{
	t_cont	*current;

	while (*head)
	{
		current = *head;
		free(current);
		current = NULL;
		*head = (*head)->next;
	}
}
