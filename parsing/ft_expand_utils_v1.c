/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils_v1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:08:18 by iassil            #+#    #+#             */
/*   Updated: 2024/04/27 22:32:28 by iassil           ###   ########.fr       */
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
		t.next_node = (*current)->next;
		*current = *newlist;
		t.last_node = ft_last_node(*newlist);
		t.last_node->next = t.next_node;
	}
	else
	{
		t.next_node = (*current)->next;
		previous->next = *newlist;
		t.last_newlist = ft_last_node(*newlist);
		t.last_node = ft_last_node(*newlist);
		t.last_node->next = t.next_node;
		if (t.last_node->next == NULL)
			*current = NULL;
		else
			*current = t.last_newlist;
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
	str = ft_split_after_expanding((*current)->token);
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

	(void)is_quote;
	(1) && (i = 0, flag = 0);
	if ((*current)->type == FILENAME)
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
	t_token	*last_node;

	if (f->is_export == 1 && ft_is_between_quotesorequal(f->check, 1))
		return ;
	f->newlist = ft_split_and_push_node(&f->head);
	ft_push_middle(f->previous, &f->head, &f->newlist);
	if (f->previous == NULL)
		*linked_list = f->head;
}
