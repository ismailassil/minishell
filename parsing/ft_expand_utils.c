/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:08:18 by iassil            #+#    #+#             */
/*   Updated: 2024/04/23 19:53:29 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_push_middle(t_token *previous, t_token **current, t_token **newlist)
{
	t_push_middle	t;

	if (!newlist || !*newlist)
		return ;
	t.tobefreed = (*current);
	if (previous == NULL)
	{
		t.nextnode = (*current)->next;
		*current = *newlist;
		t.lastnode = ft_last_node(*newlist);
		t.lastnode->next = t.nextnode;
	}
	else
	{
		t.nextnode = (*current)->next;
		previous->next = *newlist;
		t.lastnode = ft_last_node(*newlist);
		t.lastnode->next = t.nextnode;
		if ((*newlist)->next == NULL)
			*current = NULL;
		else
			*current = (*newlist)->next;
	}
	(free(t.tobefreed->token), free(t.tobefreed));
}

void	ft_token_list(t_token *current, t_token **new_list)
{
	t_token	*head;

	head = *new_list;
	if (current->type == CMD)
	{
		head->type = CMD;
		head = head->next;
	}
	while (head != NULL)
	{
		head->type = ARG;
		head = head->next;
	}
}

t_token	*ft_split_and_push_node(t_token **current)
{
	int		i;
	char	**str;
	t_token	*new_list;

	i = 0;
	new_list = NULL;
	str = ft_split_v2((*current)->token);
	ft_check_allocation(str);
	while (str[i] != 0)
	{
		if (ft_push_token(str[i], &new_list) == 0)
			(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
		free(str[i]);
		i++;
	}
	free(str);
	ft_token_list(*current, &new_list);
	return (new_list);
}

int	ft_check_after_expand(t_token **current, int is_quote)
{
	int	i;
	int	flag;

	(1) && (i = 0, flag = 0);
	if ((*current)->type == FILENAME)
		return (0);
	if (is_quote == 1)
		return (0);
	while ((*current)->token[i] != '\0')
	{
		if (ft_strchr(" \t\n\v\f\r", (*current)->token[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_split_node(t_expand_arg *f, t_token **linked_list)
{
	if (f->type == 1)
		;
	else
	{
		f->newlist = ft_split_and_push_node(&f->head);
		ft_push_middle(f->previous, &f->head, &f->newlist);
		if (f->previous == NULL)
			*linked_list = f->head;
	}
}
